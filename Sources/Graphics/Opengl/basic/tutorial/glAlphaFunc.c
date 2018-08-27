//绘制相框，此时进行Alpha测试，只绘制不透明部分的像素
glBindTexture(GL_TEXTURE_2D,texWindow);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER,0.5f);//Alpha>0.5才绘制

glBegin(GL_QUADS);
glTexCoord2f(0,0);
glVertex2f(-1.0f,-1.0f);
glTexCoord2f(0,1);
glVertex2f(-1.0f,1.0f);
glTexCoord2f(1,1);
glVertex2f(1.0f,1.0f);
glTexCoord2f(1,0);
glVertex2f(1.0f,-1.0f);
glEnd();
