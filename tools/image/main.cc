//
// Created by wangrl2016 on 2023/8/25.
//

#include <gflags/gflags.h>
#include <QApplication>
#include <QImage>
#include <QString>
#include <QPainter>

DEFINE_string(input_file1, "", "File input file");
DEFINE_string(input_file2, "", "Second input file");
DEFINE_string(background_file, "", "Background image file");
DEFINE_string(output_file, "", "Output file");

constexpr int kMargin = 20;
constexpr int kOffset = 50;
constexpr int kFontSize = 60;
constexpr int kPenWidth = 2;
constexpr int kColorPrimary40 = 0x6750A4;
QString kContentString = "";

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (FLAGS_input_file1.empty() || FLAGS_input_file2.empty())
        return EXIT_FAILURE;

    QImage image1;
    image1.load(QString::fromStdString(FLAGS_input_file1));
    QImage image2;
    image2.load(QString::fromStdString(FLAGS_input_file2));
    QImage background;
    background.load(QString::fromStdString(FLAGS_background_file));

    int width = kMargin * 2 + image1.width() > image2.width() ? image1.width() : image2.width();
    int height = kMargin * 4 + image1.height() + image2.height();

    qDebug() << "Size " << width << "x" << height;

    QImage image(width, height, QImage::Format_RGBA8888);

    for (int i = 0; i < height; i++) {
        if (kMargin <= i && i < kMargin + image1.height()) {
            for (int j = 0; j < width; j++) {
                int left = (width - image1.width()) / 2;
                if (left <= j && j < left + image1.width()) {
                    QRgb rgb = image1.pixel(j - left, i - kMargin);
                    image.setPixel(j, i, rgb);
                } else {
                    image.setPixel(j, i, background.pixel(j + kOffset, i + kOffset));
                }
            }
        } else if (kMargin * 2 + image1.height() <= i && i < kMargin * 2 + image1.height() + image2.height()) {
            for (int j = 0; j < width; j++) {
                int left = (width - image2.width()) / 2;
                if (left <= j && j < left + image2.width()) {
                    QRgb rgb = image2.pixel(j - left, i - kMargin * 2 - image1.height());
                    if (qAlpha(rgb) == 0) {
                        image.setPixel(j, i, background.pixel(j + kOffset, i + kOffset));
                    } else {
                        image.setPixel(j, i, rgb);
                    }

                } else {
                    image.setPixel(j, i, background.pixel(j + kOffset, i + kOffset));
                }
            }
        } else {
            for (int j = 0; j < width; j++) {
                image.setPixel(j, i, background.pixel(j + kOffset, i + kOffset));
            }
        }
    }

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing, true);

    QFont f;
    f.setPixelSize(kFontSize);
    painter.setFont(f);
    QPen p;
    p.setColor(QColor(kColorPrimary40));
    painter.setPen(p);
    painter.drawText(QRect(0, height / 2 - kFontSize, width, 2 * kFontSize),
                     Qt::AlignHCenter | Qt::AlignVCenter,
                     kContentString);

    p.setWidth(kPenWidth);
    painter.setPen(p);
    painter.drawRect(kMargin, kMargin, width - 2 * kMargin, height - 2 * kMargin);

    image.save(QString::fromStdString(FLAGS_output_file));
    return EXIT_SUCCESS;
}
