#!/usr/bin/python3
import argparse
import os
import subprocess
import sys
import threading
import requests

dependencies = {
    'third_party/JUCE': 'https://github.com/juce-framework/JUCE.git@69795dc8e589a9eb5df251b6dd994859bf7b3fab',
    'third_party/portsmf':'https://codeberg.org/tenacityteam/portsmf.git@3c970d64ac77bc291634f7927f7fd22e5c84d649'
}

media_file_urls = {
    'https://download.blender.org/peach/bigbuckbunny_movies/BigBuckBunny_320x180.mp4',
}


def git_executable():
    """Find the git executable.
    Returns:
        A string suitable for passing to subprocess functions, or None.
    """

    search_list = ['git', 'git.bat']
    with open(os.devnull, 'w') as devnull:
        for git in search_list:
            try:
                subprocess.call([git, '--version'], stdout=devnull)
            except (OSError,):
                continue
            return git
    return None


def git_repository_sync_is_disabled(git, directory):
    try:
        disable = subprocess.check_output(
            [git, 'config', 'sync-deps.disable'], cwd=directory)
        return disable.lower().strip() in ['true', '1', 'yes', 'on']
    except subprocess.CalledProcessError:
        return False


def is_git_toplevel(git, directory):
    """Return true iff the directory is the top level of a Git repository.
    Args:
      git (string) the git executable
      directory (string) the path into which the repository
                is expected to be checked out.
    """
    try:
        toplevel = subprocess.check_output(
            [git, 'rev-parse', '--show-toplevel'], cwd=directory).strip()
        return (os.path.normcase(os.path.realpath(directory)) ==
                os.path.normcase(os.path.realpath(toplevel.decode())))
    except subprocess.CalledProcessError:
        return False


def status(directory, commit_hash, change):
    def truncate_beginning(s, length):
        return s if len(s) <= length else '...' + s[-(length - 3):]

    def truncate_end(s, length):
        return s if len(s) <= length else s[:(length - 3)] + '...'

    dlen = 36
    directory = truncate_beginning(directory, dlen)
    commit_hash = truncate_end(commit_hash, 40)
    symbol = '>' if change else '@'
    sys.stdout.write('%-*s %s %s\n' % (dlen, directory, symbol, commit_hash))


def git_checkout_to_directory(git, repo, commit_hash, directory, verbose):
    """Checkout (and clone if needed) a Git repository.
    Args:
      git (string) the git executable
      repo (string) the location of the repository, suitable
           for passing to `git clone`.
      commit_hash (string) a commit, suitable for passing to `git checkout`
      directory (string) the path into which the repository
                should be checked out.
      verbose (boolean)
    Raises an exception if any calls to git fail.
    """
    if not os.path.isdir(directory):
        subprocess.check_call(
            [git, 'clone', '--quiet', '--no-checkout', repo, directory])
        subprocess.check_call([git, 'checkout', '--quiet', commit_hash],
                              cwd=directory)
        if verbose:
            status(directory, commit_hash, True)
        return

    if not is_git_toplevel(git, directory):
        # if the directory exists, but isn't a git repo, you will modify
        # the parent repository, which isn't what you want.
        sys.stdout.write('%s\n  IS NOT TOP-LEVEL GIT DIRECTORY.\n' % directory)
        return

    # Check to see if this repo is disabled.  Quick return.
    if git_repository_sync_is_disabled(git, directory):
        sys.stdout.write('%s\n  SYNC IS DISABLED.\n' % directory)
        return

    with open(os.devnull, 'w') as devnull:
        # If this fails, we will fetch before trying again.  Don't spam user
        # with error information.
        if 0 == subprocess.call([git, 'checkout', '--quiet', commit_hash],
                                cwd=directory, stderr=devnull):
            # if this succeeds, skip slow `git fetch`.
            if verbose:
                status(directory, commit_hash, False)  # Success.
            return

    # If the repo has changed, always force use of the correct repo.
    # If origin already points to repo, this is a quick no-op.
    subprocess.check_call(
        [git, 'remote', 'set-url', 'origin', repo], cwd=directory)

    subprocess.check_call([git, 'fetch', '--quiet'], cwd=directory)

    subprocess.check_call([git, 'checkout', '--quiet', commit_hash], cwd=directory)

    if verbose:
        status(directory, commit_hash, True)  # Success.


def git_sync_deps(verbose):
    git = git_executable()

    for directory in dependencies:
        for other_dir in dependencies:
            if directory.startswith(other_dir + '/'):
                raise Exception('%r is parent of %r' % (other_dir, directory))
    list_of_arg_lists = []
    for directory in sorted(dependencies):
        if not isinstance(dependencies[directory], str):
            if verbose:
                sys.stdout.write('Skipping "%s".\n' % directory)
            continue
        if '@' in dependencies[directory]:
            repo, commit_hash = dependencies[directory].split('@', 1)
        else:
            raise Exception("Please specify commit")

        relative_directory = os.path.join(os.curdir, directory)

        list_of_arg_lists.append(
            (git, repo, commit_hash, relative_directory, verbose))

    multi_thread(git_checkout_to_directory, list_of_arg_lists)


def multi_thread(function, list_of_arg_lists):
    anything_failed = False
    threads = []

    def hook():
        nonlocal anything_failed
        anything_failed = True

    threading.excepthook = hook
    for args in list_of_arg_lists:
        thread = threading.Thread(None, function, None, args)
        thread.start()
        threads.append(thread)
    for thread in threads:
        thread.join()
    if anything_failed:
        raise Exception("Thread failure detected")


def download_media_file():
    for media_file_url in media_file_urls:
        local_file_path = os.path.join('res/media', media_file_url.split('/')[-1])
        r = requests.get(media_file_url, stream=True)
        print(local_file_path)
        with open(local_file_path, 'wb') as f:
            for chunk in r.iter_content(chunk_size=1024*1024):
                if chunk:
                    f.write(chunk)


def build_conan_packages():
    pass


def main(args):
    verbose = not bool(os.environ.get('GIT_SYNC_DEPS_QUIET', False))

    git_sync_deps(verbose)

    download_media_file()

    build_conan_packages()

    output_folder = '--output-folder=' + args.output_folder
    build_type = '--settings=build_type=' + args.build_type
    # subprocess.check_call(['conan', 'install', '.', output_folder, '--build=missing', build_type])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog='PROG',
                                     conflict_handler='resolve')
    parser.add_argument('-b', '--build_type', default='Debug', help='Build type, Debug or Release')
    parser.add_argument('-o', '--output_folder', default='cmake-build-debug',
                        help='Output directory, e.g. cmake-build-release')

    exit(main(parser.parse_args()))
