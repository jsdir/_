#include <stdlib.h>
#include <math.h>
#include <clutter/clutter.h>

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

static void
plate2anim (ClutterTimeline *timeline,
            const gchar     *marker_name,
            guint            frame_num,
            ClutterActor    *bg)
{
	clutter_actor_set_easing_duration (bg, 833);
	clutter_actor_save_easing_state (bg);
	clutter_actor_set_easing_mode (bg, CLUTTER_EASE_OUT_EXPO);
	clutter_actor_set_x_align (bg, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_restore_easing_state (bg);
}

static void
plate3anim (ClutterTimeline *timeline,
            const gchar     *marker_name,
            guint            frame_num,
            ClutterActor    *labelbg)
{
	clutter_actor_save_easing_state (labelbg);
	clutter_actor_set_easing_duration (labelbg, 583);
	clutter_actor_set_easing_mode (labelbg, CLUTTER_EASE_OUT_CUBIC);
	clutter_actor_set_width(labelbg, 400);
	clutter_actor_restore_easing_state (labelbg);
}

static void
plate4anim (ClutterTimeline *timeline,
            const gchar     *marker_name,
            guint            frame_num,
            ClutterActor    *fixed)
{
	clutter_actor_save_easing_state (fixed);
	clutter_actor_set_easing_duration (fixed, 1250);
	clutter_actor_set_easing_mode (fixed, CLUTTER_EASE_OUT_EXPO);
	clutter_actor_set_position(fixed, 0, 0);
	clutter_actor_restore_easing_state (fixed);
}

static void
plate5anim (ClutterTimeline *timeline,
            const gchar     *marker_name,
            guint            frame_num,
            ClutterActor    *lowerInner)
{
	clutter_actor_save_easing_state (lowerInner);
	clutter_actor_set_easing_duration (lowerInner, 875);
	clutter_actor_set_easing_mode (lowerInner, CLUTTER_EASE_OUT_EXPO);
	clutter_actor_set_position(lowerInner, 0, 0);
	clutter_actor_restore_easing_state (lowerInner);
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
draw_1 (ClutterCanvas *canvas,
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

  cairo_set_source_rgba (cr, 0.14*.2, 0.14, 0.36*.5, 0.5);
  cairo_fill_preserve (cr);

  /* we're done drawing */
  return TRUE;
}

static void
on_actor_resize (ClutterActor           *actor,
                 const ClutterActorBox  *allocation,
                 ClutterAllocationFlags  flags,
                 gpointer                user_data)
{
  float width, height;

  /* match the canvas size to the actor's */
  clutter_actor_get_size (actor, &width, &height);
  clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)),
                           ceilf (width),
                           ceilf (height));
}

int
main (int argc, char *argv[])
{
	ClutterActor *stage, *box, *bg, *bg2, *inset, *labelContainer,
	             *contentContainer, *labelbg, *fixed, *upper, *lower, *lowerInner;
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
	clutter_actor_add_constraint (box, clutter_bind_constraint_new (stage, CLUTTER_BIND_SIZE, 0.0));
	clutter_actor_set_background_color (box, CLUTTER_COLOR_WHITE);
	clutter_actor_set_layout_manager (box, layout);
	clutter_actor_add_constraint (box, clutter_align_constraint_new (stage, CLUTTER_ALIGN_X_AXIS, 1));
	clutter_actor_set_name (box, "box");
	clutter_actor_add_child (stage, box);


	bg = clutter_actor_new ();
	//clutter_actor_set_background_color (bg, clutter_color_new (50, 50, 50, 255));
	clutter_actor_set_name (bg, "background");
	clutter_actor_set_reactive (bg, TRUE);
	//clutter_actor_set_x_expand (bg, TRUE);
	//clutter_actor_set_y_expand (bg, TRUE);
	clutter_actor_set_x_align (bg, CLUTTER_ACTOR_ALIGN_END);
	clutter_actor_set_y_align (bg, CLUTTER_ACTOR_ALIGN_FILL);
	canvas1 = clutter_canvas_new ();
	clutter_canvas_set_size (CLUTTER_CANVAS (canvas1), 300, 300);
	clutter_actor_set_content (bg, canvas1);
	/*clutter_actor_set_content_scaling_filters (bg2,
		 CLUTTER_SCALING_FILTER_TRILINEAR,
		 CLUTTER_SCALING_FILTER_LINEAR);*/
	g_object_unref (canvas1);
	clutter_actor_add_child (box, bg);


	bg2 = clutter_actor_new ();
	//clutter_actor_set_background_color (bg2, clutter_color_new (0, 100, 100, 255*.5));
	clutter_actor_set_name (bg2, "background");
	clutter_actor_set_reactive (bg2, TRUE);
	clutter_actor_set_size (bg2, 0, 0);
	//clutter_actor_set_x_expand (bg2, TRUE);
	//clutter_actor_set_y_expand (bg2, TRUE);
	clutter_actor_set_x_align (bg2, CLUTTER_ACTOR_ALIGN_END);
	clutter_actor_set_y_align (bg2, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_set_clip_to_allocation(bg2, TRUE);
	clutter_actor_add_child (box, bg2);
	clutter_actor_set_layout_manager (bg2, clutter_box_layout_new ());
	canvas = clutter_canvas_new ();
	clutter_canvas_set_size (CLUTTER_CANVAS (canvas), 300, 300);
	clutter_actor_set_content (bg2, canvas);
	/*clutter_actor_set_content_scaling_filters (bg2,
		 CLUTTER_SCALING_FILTER_TRILINEAR,
		 CLUTTER_SCALING_FILTER_LINEAR);*/
	g_object_unref (canvas);


	inset = clutter_actor_new ();
	//clutter_actor_set_background_color (inset, clutter_color_new (255, 0, 0, 255));
	clutter_actor_set_name (inset, "inset");
	clutter_actor_set_reactive (inset, TRUE);


	clutter_actor_set_margin_top (inset, 18);
	clutter_actor_set_margin_right (inset, 18);
	clutter_actor_set_margin_bottom (inset, 18);
	clutter_actor_set_margin_left (inset, 48);
	//clutter_actor_set_x_expand (inset, TRUE);
	//clutter_actor_set_y_expand (inset, TRUE);
	clutter_actor_set_x_align (inset, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_set_y_align (inset, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_set_clip_to_allocation(inset, TRUE);
	clutter_actor_add_child (bg2, inset);


	layout = clutter_box_layout_new ();
	clutter_box_layout_set_vertical (CLUTTER_BOX_LAYOUT (layout),
	                                    TRUE);
	clutter_box_layout_set_spacing (CLUTTER_BOX_LAYOUT (layout), 5);
	clutter_actor_set_layout_manager (inset, layout);


	labelContainer = clutter_actor_new ();
	clutter_actor_set_size (labelContainer, 0, 35);
	//clutter_actor_set_background_color (labelContainer, clutter_color_new (34, 134, 158, 255));
	clutter_actor_set_name (labelContainer, "labelContainer");
	clutter_actor_set_reactive (labelContainer, TRUE);
	//clutter_actor_set_x_expand (labelContainer, TRUE);
	//clutter_actor_set_y_expand (labelContainer, TRUE);
	clutter_actor_add_child (inset, labelContainer);

	labelContainer_l = clutter_bin_layout_new (CLUTTER_BIN_ALIGNMENT_CENTER,
			CLUTTER_BIN_ALIGNMENT_CENTER);
	clutter_actor_set_layout_manager (labelContainer, labelContainer_l);


	labelbg = clutter_actor_new ();
	clutter_actor_set_background_color (labelbg, clutter_color_new (34, 134, 158, 255));
	clutter_actor_set_name (labelbg, "labelbg");
	//clutter_actor_set_x_expand (labelbg, TRUE);
	clutter_actor_set_size (labelbg, 0, 35);
	clutter_actor_set_x_align (labelbg, CLUTTER_ACTOR_ALIGN_START);
	clutter_actor_set_y_align (labelbg, CLUTTER_ACTOR_ALIGN_FILL);
	clutter_actor_add_child (labelContainer, labelbg);


	contentContainer = clutter_actor_new ();
	clutter_actor_set_size (contentContainer, 0, 0);

	clutter_actor_set_background_color (contentContainer, clutter_color_new (0.290196*255, 0.427451*255, 0.462745*255, 255));
	clutter_actor_set_name (contentContainer, "labelContainer");
	//clutter_actor_set_x_expand (contentContainer, TRUE);
	//clutter_actor_set_y_expand (contentContainer, TRUE);
	clutter_actor_set_layout_manager (contentContainer, clutter_fixed_layout_new ());
	clutter_actor_add_child (inset, contentContainer);

	fixed = clutter_actor_new ();
	clutter_actor_set_background_color (fixed, clutter_color_new (9, 53, 71, 255));
	clutter_actor_set_name (fixed, "fixed");
	clutter_actor_set_size (fixed, 582, 210-40);
	clutter_actor_set_position (fixed, 582, 0);
	layoutFixed = clutter_box_layout_new ();
	clutter_box_layout_set_vertical (CLUTTER_BOX_LAYOUT (layoutFixed),
		                                TRUE);
	clutter_box_layout_set_spacing (CLUTTER_BOX_LAYOUT (layoutFixed), 8);
	clutter_actor_set_layout_manager (fixed, layoutFixed);
	clutter_actor_add_child (contentContainer, fixed);


	//------------------------------------------------------------------------//

	lower = clutter_actor_new ();
	clutter_actor_set_size (lower, 0, 0);
	clutter_actor_set_name (lower, "lower");
	//clutter_actor_set_x_expand (lower, TRUE);
	//clutter_actor_set_y_expand (lower, TRUE);
	clutter_actor_set_margin_right (lower, 8);
	clutter_actor_set_margin_top (lower, 8);
	clutter_actor_set_margin_left (lower, 8);
	clutter_actor_set_layout_manager (lower, clutter_fixed_layout_new ());
	clutter_actor_set_clip_to_allocation(lower, TRUE);
	clutter_actor_add_child (fixed, lower);

	lowerInner = clutter_actor_new ();
	clutter_actor_set_background_color (lowerInner, clutter_color_new (255, 255, 255, 30));
	clutter_actor_set_name (lowerInner, "fixed");
	clutter_actor_set_size (lowerInner, 566, 113);
	clutter_actor_set_position (lowerInner, 566, 0);
	clutter_actor_add_child (lower, lowerInner);


	upper = clutter_actor_new ();
	clutter_actor_set_size (upper, 0, 33);
	clutter_actor_set_name (upper, "upper");
	clutter_actor_set_x_expand (upper, TRUE);
	//clutter_actor_set_y_expand (upper, TRUE);
	clutter_actor_set_margin_bottom (upper, 8);
	clutter_actor_set_margin_right (upper, 8);
	clutter_actor_set_margin_left (upper, 8);
	//clutter_actor_set_layout_manager (upper, clutter_fixed_layout_new ());
	clutter_actor_add_child (fixed, upper);


	timeline = clutter_timeline_new (57/24.*1000);
	clutter_timeline_add_marker_at_time(timeline, "first", (40-35)/24.*1000);
	clutter_timeline_add_marker_at_time(timeline, "second", (46-35)/24.*1000);
	clutter_timeline_add_marker_at_time(timeline, "third", (51-35)/24.*1000);
	clutter_timeline_add_marker_at_time(timeline, "fourth", (52-35)/24.*1000);
	clutter_timeline_add_marker_at_time(timeline, "fifth", (58-35)/24.*1000);

	g_signal_connect (timeline, "marker-reached::first", G_CALLBACK (plate1anim), bg);
	g_signal_connect (timeline, "marker-reached::second", G_CALLBACK (plate2anim), bg2);
	g_signal_connect (timeline, "marker-reached::third", G_CALLBACK (plate3anim), labelbg);
	g_signal_connect (timeline, "marker-reached::fourth", G_CALLBACK (plate4anim), fixed);
	g_signal_connect (timeline, "marker-reached::fifth", G_CALLBACK (plate5anim), lowerInner);
	g_signal_connect (canvas1, "draw", G_CALLBACK (draw_1), NULL);
	g_signal_connect (bg, "paint", G_CALLBACK (on_actor_resize), canvas);
	g_signal_connect (canvas, "draw", G_CALLBACK (draw), NULL);
	g_signal_connect (bg2, "paint", G_CALLBACK (on_actor_resize), canvas);


	clutter_content_invalidate (canvas);

	clutter_timeline_start (timeline);
	clutter_main ();

	return (EXIT_SUCCESS);
}
