#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_u.h"
#include "agg_renderer_scanline.h"
#include "agg_pixfmt_rgb.h"
#include "platform/agg_platform_support.h"
#include "agg_ellipse.h"
#include "agg_conv_contour.h"
#include "agg_conv_stroke.h"
class the_application : public agg::platform_support
{
public:
    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y)
    {
    }
    virtual void on_draw()
    {
        //Rendering Buffer
        agg::rendering_buffer &rbuf = rbuf_window();
        agg::pixfmt_bgr24  pixf(rbuf);
       
        // Renderers
        typedef agg::renderer_base<agg::pixfmt_bgr24> renderer_base_type;
        renderer_base_type renb(pixf);
        typedef agg::renderer_scanline_aa_solid<renderer_base_type> renderer_scanline_type;
        renderer_scanline_type rensl(renb);
       
        // Vertex Source
        agg::ellipse ell(100,100,50,50);
       
        // Coordinate conversion pipeline
        typedef agg::conv_contour<agg::ellipse> ell_cc_type;
        ell_cc_type ccell(ell);
       
        typedef agg::conv_stroke<ell_cc_type> ell_cc_cs_type;
        ell_cc_cs_type csccell(ccell);
       
        // Scanline Rasterizer
        agg::rasterizer_scanline_aa<> ras;
        agg::scanline_u8 sl;
       
        // Draw
        renb.clear(agg::rgba8(255,255,255));
        for(int i=0; i<5; i++)
        {
            ccell.width(i*20);
            ras.add_path(csccell);
            rensl.color( agg::rgba8(0,0,i*50));
            agg::render_scanlines(ras,sl,rensl);
        }
    }
};
int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_bgr24, false);
    app.caption("AGG Example. Anti-Aliasing Demo");
    if(app.init(600, 400, agg::window_resize))
    {
        return app.run();
    }
    return -1;
}
