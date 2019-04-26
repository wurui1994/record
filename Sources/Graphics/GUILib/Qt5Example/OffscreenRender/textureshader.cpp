#include <QtWidgets/QApplication>

#include <QtOpenGL/QGLFormat>
#include <QtOpenGL/QGLPixelBuffer>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QImage image("/Users/wurui/untitled/lenna.png");

    QGLPixelBuffer frameBuffer(image.size());
    frameBuffer.makeCurrent();
    
    QOpenGLShaderProgram* program = nullptr;
	QOpenGLTexture* texture = nullptr;
	QOpenGLBuffer vbo;
	
	static const float coords[4][3] =
	{ { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } };

	QVector<GLfloat> vertData;

	for (int j = 0; j < 4; ++j) 
    {
		// vertex position
		vertData.append(coords[j][0]);
		vertData.append(coords[j][1]);
		vertData.append(0 * coords[j][2]);
		// texture coordinate
		vertData.append(j == 0 || j == 3);
		vertData.append(j == 0 || j == 1);
	}

	vbo.create();
	vbo.bind();
	vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex);
	const char *vsrc =
		"attribute highp vec4 vertex;\n"
		"attribute mediump vec4 texCoord;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = vertex;\n"
		"    texc = texCoord;\n"
		"}\n";
	vshader->compileSourceCode(vsrc);

	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment);
	const char *fsrc =
		"uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = texture2D(texture, texc.st);\n"
		"}\n";
	fshader->compileSourceCode(fsrc);

	program = new QOpenGLShaderProgram;
	program->addShader(vshader);
	program->addShader(fshader);
	program->bindAttributeLocation("vertex", 0);
	program->bindAttributeLocation("texCoord", 1);
	program->link();
	
	program->bind();
	program->setUniformValue("texture", 0);

	program->enableAttributeArray(0);
	program->enableAttributeArray(1);
	program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
	program->setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

	texture = new QOpenGLTexture(image.mirrored(true,false));
	texture->bind();
	glDrawArrays(GL_QUADS, 0, 4);

	program->release();
    
    // At last, the frame buffer was saved as an image
    QImage pImage = frameBuffer.toImage();
    pImage.save(QString::fromLocal8Bit("opengl.png"));

    frameBuffer.doneCurrent();
    //return a.exec();
}