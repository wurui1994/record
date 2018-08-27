// ShaderToy Sin
void main()
{
    float time=iGlobalTime*1.0;
    vec2 uv = gl_FragCoord.xy/iResolution.xy ;
    if(abs(sin(uv.x*6.)/2.+0.5-uv.y) < 0.003)
    {
        gl_FragColor.b = 1.;
    }    
}
