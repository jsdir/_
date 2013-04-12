#include <stdlib.h>
#include <math.h>
#include <clutter/clutter.h>
#include <stdio.h>

static void
plate1anim (ClutterTimeline *timeline,
            const gchar     *marker_name,
            guint            frame_num,
            ClutterActor    *bg)
{
	clutter_actor_set_easing_duration (bg, 750);
	clutter_actor_save_easing_state (bg);
	clutter_actor_set_easing_mode (bg, CLUTTER_EASE_OUT_CIRC);
	clutter_actor_set_x_align (bg, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_restore_easing_state (bg);
}

static gboolean
draw (ClutterCanvas *canvas,
            cairo_t       *cr,
            int            width_raw,
            int            height_raw)
{
  /* rounded rectangle taken from:
   *
   *   http://cairographics.org/samples/rounded_rectangle/
   *
   * we leave 1 pixel around the edges to avoid jagged edges
   * when rotating the actor
   */
  double x             = 1.0,        /* parameters like cairo_rectangle */
         y             = 1.0,
         width         = width_raw - 2.0,
         height        = height_raw - 2.0,
         corner_radius = 5.0,
         tab_radius    = 20.0;

  double radius = corner_radius ;
  double degrees = M_PI / 180.0;
  cairo_pattern_t *gradient;
  cairo_surface_t *image;
  cairo_pattern_t *imagelol;
  cairo_surface_t *image2;
  cairo_pattern_t *imagelol2;

  cairo_save (cr);
  cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
  cairo_paint (cr);
  cairo_restore (cr);

  cairo_new_sub_path (cr);
  cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
  /*bottom-left*/cairo_arc (cr, x + radius + 30, y + height - radius, radius, 90 * degrees, 180 * degrees);
  cairo_arc_negative (cr, x + 30 - tab_radius, 225, tab_radius, 0 * degrees, -45 * degrees);
  cairo_arc (cr, x + tab_radius, 255 - 75, tab_radius, 135 * degrees, 180 * degrees);
  cairo_arc (cr, x + tab_radius, 255 - 75 - 85, tab_radius, 180 * degrees, 225 * degrees);
  cairo_arc_negative (cr, x + 30 - tab_radius, 255 - 75 - 85 - 45, tab_radius, 45 * degrees, 0 * degrees);
  /*top-left*/cairo_arc (cr, x + radius + 30, y + radius, radius, 180 * degrees, 270 * degrees);
  cairo_close_path (cr);

  cairo_set_source_rgba (cr, 0.145098*1.7, 0.317647*1.6, 0.380392*1.5, 0.6);
  cairo_fill_preserve (cr);

  gradient = cairo_pattern_create_linear(0.0, 0.0, 0.0, 60);
  cairo_pattern_add_color_stop_rgba(gradient, 1, 0, 0, 0, 0);
  cairo_pattern_add_color_stop_rgba(gradient, 0, 1*.7, 1*.9, 1, .15);
  cairo_set_source(cr, gradient);
  cairo_fill_preserve(cr);

  gradient = cairo_pattern_create_linear(0.0, 0.0, 50.0, 0.0);
  cairo_pattern_add_color_stop_rgba(gradient, 1, 0, 0, 0, 0);
  cairo_pattern_add_color_stop_rgba(gradient, 0, 1*.7, 1*.9, 1, .08);
  cairo_set_source(cr, gradient);
  cairo_fill_preserve(cr);

  /*image = cairo_image_surface_create_from_png("/home/jason/workspace/lol/src/noise.png");
  imagelol = cairo_pattern_create_for_surface(image);
  cairo_set_source(cr, imagelol);
  cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
  cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
  cairo_clip(cr);
  cairo_paint_with_alpha(cr, .1);*/
/*
  image2 = cairo_image_surface_create_from_png("/home/jason/Desktop/lol.png");
  imagelol2 = cairo_pattern_create_for_surface(image2);
  cairo_set_source(cr, imagelol2);
  cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
  cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
  cairo_paint_with_alpha(cr, .25);
  *//* we're done drawing */
  return TRUE;
}

static gboolean
idle_resize (gpointer data)
{
  ClutterActor *actor = data;
  float width, height;

  /* match the canvas size to the actor's */
  clutter_actor_get_size (actor, &width, &height);
  clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)),
                           ceilf (width),
                           ceilf (height));
  clutter_content_invalidate (CLUTTER_CANVAS (clutter_actor_get_content (actor)));
  /* remove the timeout */
  return G_SOURCE_CONTINUE;
}

int
main (int argc, char *argv[])
{
	ClutterActor *stage, *box;
	ClutterLayoutManager *layout, *labelContainer_l, *layoutFixed;
	ClutterTimeline *timeline;
	ClutterContent *canvas, *canvas1;

	ClutterColor color_with_trans = {0,0,0,0};
	clutter_x11_set_use_argb_visual (TRUE);

	if (clutter_init (&argc, &argv) != CLUTTER_INIT_SUCCESS)
	    return (1);

	/* prepare the stage */
	stage = clutter_stage_new ();
	clutter_stage_set_use_alpha (CLUTTER_STAGE (stage), TRUE);
	clutter_stage_set_color (CLUTTER_STAGE (stage), &color_with_trans);
	clutter_stage_set_title (CLUTTER_STAGE (stage), "IPLocation Database");
	clutter_actor_set_background_color (stage, CLUTTER_COLOR_WHITE);
	clutter_actor_set_size (stage, 648, 246);
	clutter_stage_set_user_resizable (CLUTTER_STAGE (stage), TRUE);
	clutter_actor_show (stage);
	g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);

	layout = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER,
			CLUTTER_BIN_ALIGNMENT_CENTER);

	box = clutter_actor_new ();
	clutter_actor_set_reactive (box, TRUE);
	clutter_actor_add_constraint (box, clutter_bind_constraint_new (stage, CLUTTER_BIND_SIZE, 0.0));
	clutter_actor_set_background_color (box, CLUTTER_COLOR_WHITE);
	clutter_actor_set_layout_manager (box, layout);
	clutter_actor_add_constraint (box, clutter_align_constraint_new (stage, CLUTTER_ALIGN_X_AXIS, 1));
	clutter_actor_set_name (box, "box");
	canvas = clutter_canvas_new ();
	clutter_canvas_set_size (CLUTTER_CANVAS (canvas), 300, 300);
	clutter_actor_set_content (box, canvas);
	g_object_unref (canvas);
	clutter_actor_add_child (stage, box);

  
	g_signal_connect (canvas, "draw", G_CALLBACK (draw), NULL);
	g_signal_connect (box, "paint", G_CALLBACK (idle_resize), canvas);
	
	clutter_content_invalidate (canvas);
	clutter_main ();

	return (EXIT_SUCCESS);
}
