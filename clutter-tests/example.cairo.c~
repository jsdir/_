#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>
#include <math.h>
#include <cairo.h>
#include <stdlib.h>

// six empty rectangles and our stage
ClutterActor *stage = NULL;
ClutterActor *rect1 = NULL;
ClutterActor *rect2 = NULL;
ClutterActor *rect3 = NULL;
ClutterActor *rect4 = NULL;
ClutterActor *rect5 = NULL;
ClutterActor *rect6 = NULL;
ClutterActor *rect7 = NULL;
ClutterActor *rect8 = NULL;

cairo_surface_t *image = NULL;

// the create_rect() function needs to create actual rectangles rather than text boxes
ClutterActor *create_rect() {
  ClutterActor *rect = clutter_rectangle_new();
  clutter_actor_set_size(rect, 256, 128);
  clutter_actor_set_position(rect, 256, 256);
  clutter_actor_set_anchor_point(rect, 128, 64);
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), rect);
  clutter_actor_show (rect);

  return rect;
}

void move_rect(ClutterActor *rect) {
  clutter_actor_animate (rect,
          CLUTTER_EASE_IN_OUT_CUBIC,
          2500,
          "x", (float)(rand() % 1200),
          "y", (float)(rand() % 780),
          "width", (float)(rand() % 600),
          "height", (float)(rand() % 600),
          //"rotation-angle-z", (float)(rand() % 360),
          NULL);
}


// we'll be filling in this function later
void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data) {
   move_rect(rect1);
   move_rect(rect2);
   move_rect(rect3);
   move_rect(rect4);
   move_rect(rect5);
   move_rect(rect6);
   move_rect(rect7);
   move_rect(rect8);
}

static gboolean
draw_content (ClutterCanvas *canvas,
              cairo_t       *cr,
              int            surface_width,
              int            surface_height)
{
  /* rounded rectangle taken from:
   *
   *   http://cairographics.org/samples/rounded_rectangle/
   *
   * we leave 1 pixel around the edges to avoid jagged edges
   * when rotating the actor
   */
  double x             = 0.0,        /* parameters like cairo_rectangle */
         y             = 0.0,
         width         = surface_width - 0.0,
         height        = surface_height - 0.0,
         aspect        = 1.0,     /* aspect ratio */
         corner_radius = height / 20.0;   /* and corner curvature radius */

  double radius = corner_radius / aspect;
  double degrees = M_PI / 180.0;
  int              w, h;
  
  
  cairo_save (cr);
  cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
  cairo_paint (cr);
  cairo_restore (cr);

  cairo_new_sub_path (cr);
  cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
  cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
  cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
  cairo_close_path (cr);
  
  /*w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  cairo_scale (cr, width/w, height/h);*/
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
  cairo_fill (cr);

  /* we're done drawing */
  return TRUE;
}

static void
on_stage_pre_paint (ClutterActor *actor)
{
  cogl_set_depth_test_enabled (TRUE);
}

static void
on_stage_post_paint (ClutterActor *actor)
{
  cogl_set_depth_test_enabled (FALSE);
}

static void
on_actor_resize (ClutterActor           *actor,
                 const ClutterActorBox  *allocation,
                 ClutterAllocationFlags  flags,
                 gpointer                user_data)
{
    float width, height;
  clutter_actor_get_size (actor, &width, &height);
  clutter_canvas_set_size (CLUTTER_CANVAS (clutter_actor_get_content (actor)),
                           ceilf (width),
                           ceilf (height));
}

int main(int argc, char *argv[]) {
  image = cairo_image_surface_create_from_png ("/home/Sommer_Jason/Pictures/moulin.png");
  clutter_x11_set_use_argb_visual (TRUE);
  int lol = clutter_init (&argc, &argv);

  ClutterColor stage_color = { 0, 0, 0, 255 };
  ClutterContent *canvas1, *canvas2, *canvas3, *canvas4, *canvas5, *canvas6, *canvas7, *canvas8;

  stage = clutter_stage_get_default();
  clutter_actor_set_size (stage, 512, 512);
  clutter_stage_set_user_resizable (CLUTTER_STAGE (stage), TRUE);
  clutter_stage_set_use_alpha (CLUTTER_STAGE (stage), TRUE);
  clutter_stage_set_color (CLUTTER_STAGE(stage), &stage_color);
  clutter_actor_set_opacity (stage, 0);

  rect1 = create_rect();
  rect2 = create_rect();
  rect3 = create_rect();
  rect4 = create_rect();
  rect5 = create_rect();
  rect6 = create_rect();
  rect7 = create_rect();
  rect8 = create_rect();
  
  /* our 2D canvas, courtesy of Cairo */
  canvas1 = clutter_canvas_new ();
  canvas2 = clutter_canvas_new ();
  canvas3 = clutter_canvas_new ();
  canvas4 = clutter_canvas_new ();
  canvas5 = clutter_canvas_new ();
  canvas6 = clutter_canvas_new ();
  canvas7 = clutter_canvas_new ();
  canvas8 = clutter_canvas_new ();
  
  clutter_actor_set_content (rect1, canvas1);
  clutter_actor_set_content (rect2, canvas2);
  clutter_actor_set_content (rect3, canvas3);
  clutter_actor_set_content (rect4, canvas4);
  clutter_actor_set_content (rect5, canvas5);
  clutter_actor_set_content (rect6, canvas6);
  clutter_actor_set_content (rect7, canvas7);
  clutter_actor_set_content (rect8, canvas8);
  
  g_object_unref (canvas1);
  g_object_unref (canvas2);
  g_object_unref (canvas3);
  g_object_unref (canvas4);
  g_object_unref (canvas5);
  g_object_unref (canvas6);
  g_object_unref (canvas7);
  g_object_unref (canvas8);

  g_signal_connect (canvas1, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas2, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas3, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas4, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas5, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas6, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas7, "draw", G_CALLBACK (draw_content), NULL);
  g_signal_connect (canvas8, "draw", G_CALLBACK (draw_content), NULL);

  g_signal_connect (rect1, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect2, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect3, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect4, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect5, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect6, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect7, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  g_signal_connect (rect8, "allocation_changed", G_CALLBACK (on_actor_resize), NULL);
  
  g_signal_connect (stage, "paint", G_CALLBACK (on_stage_pre_paint), NULL);
  g_signal_connect_after (stage, "paint", G_CALLBACK (on_stage_post_paint), NULL);
  g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);

  g_signal_connect (stage, "button-press-event", G_CALLBACK (on_stage_button_press), NULL);
  clutter_stage_set_title(CLUTTER_STAGE(stage), "Spinny boxes ahoy!");
  clutter_actor_show (stage);
  
  clutter_content_invalidate (canvas1);
  clutter_content_invalidate (canvas2);
  clutter_content_invalidate (canvas3);
  clutter_content_invalidate (canvas4);
  clutter_content_invalidate (canvas5);
  clutter_content_invalidate (canvas6);
  clutter_content_invalidate (canvas7);
  clutter_content_invalidate (canvas8);
  
  clutter_main ();

  return EXIT_SUCCESS;
}
