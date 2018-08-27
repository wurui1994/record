#include <QApplication>
#include <QtAV/QtAV>
#include <QtAVWidgets>

using namespace QtAV;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	VideoRenderer *renderer = VideoRenderer::create(VideoRendererId_Widget);
    if (!renderer) return 1;
    renderer->widget()->setAttribute(Qt::WA_DeleteOnClose);
    renderer->setOutAspectRatioMode(VideoRenderer::VideoAspectRatio);
    renderer->widget()->resize(renderer->widget()->width(), renderer->widget()->width()*9/16);
    renderer->widget()->show();
    AVPlayer player;
    player.addVideoRenderer(renderer);
    player.play("F:\\Subtitles\\Zootopia.2016.1080p.BluRay.x264-SPARKS.mkv");
    return app.exec();
}
