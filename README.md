# Character

### How to run project

* Configure Qt framework

```
CMAKE_PREFIX_PATH=~/Qt/6.4.1/macos
```
* Install conan packages

### Cross building

```
conan create . --profile:host=ios_profile --profile:build=ios_profile
```

### Reference

* [Google Material Design](https://m3.material.io/)
* [ADSR Envelope](https://en.wikipedia.org/wiki/Synthesizer#ADSR_envelope)
