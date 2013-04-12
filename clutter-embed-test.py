from gi.repository import Gtk, Clutter, GtkClutter, Cogl
import random

class RoundedRectangle(Clutter.Actor):
    """
    Custom actor used to draw a rectangle that can have rounded corners
    """
    __gtype_name__ = 'RoundedRectangle'

    def __init__(self, width, height, arc, step, 
        color=None, border_color=None, border_width=0):
        """
        Creates a new rounded rectangle
        """
        super(RoundedRectangle, self).__init__()
        self._width = width
        self._height = height
        self._arc = arc
        self._step = step
        if color:
            self._color = color
        else:
            self._color = Clutter.Color.new(random.randint(0,255),
        		random.randint(0,255), random.randint(0,255), 255)
        if border_color:
            self._border_color = border_color
        else:
            self._border_color = Clutter.Color.new(random.randint(0,255),
        		random.randint(0,255), random.randint(0,255), 255)
        self._border_width = border_width

    def do_paint(self):

        # Draw a rectangle for the clipping
        Cogl.path_round_rectangle(0, 0, self._width, self._height, self._arc, self._step)
        Cogl.path_close()
       	Cogl.path_fill() 
        # Start the clip
        # Cogl.clip_push_from_path()

        # set color to border color
        #Cogl.set_source_color(self._border_color)
        # draw the rectangle for the border which is the same size and the
        # object
        Cogl.path_round_rectangle(0, 0, self._width, self._height, self._arc, self._step)
        Cogl.path_close()
        # color the path usign the border color
        ##Cogl.path_fill() 
        # set the color of the filled area
        #Cogl.set_source_color(self._color)
        # draw the content with is the same size minus the wirth of the border
        # finish the clip
        ##Cogl.path_round_rectangle(self._border_width, self._border_width, 
        ##    self._width - self._border_width, 
        ##    self._height - self._border_width, self._arc, self._step)
        ##Cogl.path_fill() 
        ##Cogl.path_close()
        
        ##Cogl.clip_pop()

    def set_color(self, color):
        self._color = color
        self.queue_redraw()
        
    def get_border_width(self):
        return self._border_width
        
    def set_border_width(self, width):
        self._border_width = width
        self.queue_redraw()
        
    def get_border_color(color):
        return self._border_color
        
    def set_border_color(self, color):
        self._border_color = color
        self.queue_redraw()

def clicked(event):
    actor = RoundedRectangle(200, 200, 5, 0.1)
    actor.set_size(100, 100)
    actor.set_y_align(Clutter.ActorAlign.FILL)
    actor.set_x_align(Clutter.ActorAlign.FILL)
    #actor.set_background_color(Clutter.Color.new(random.randint(0,255),
    #    random.randint(0,255), random.randint(0,255), 255))
    stage.add_actor(actor)

GtkClutter.init([])

window = Gtk.Window.new(Gtk.WindowType.TOPLEVEL)
vbox = Gtk.VBox.new(False, 6)
window.add(vbox)
vbox.show()
button = Gtk.Button("New Actor")
vbox.pack_end(button, False, False, 0)
button.show()

window.connect("hide", Gtk.main_quit)

embed = GtkClutter.Embed.new()
vbox.pack_start(embed, True, True, 0)
embed.show()

embed.set_size_request(150, 500)

stage = embed.get_stage()
stage.set_color(Clutter.Color.new(0x00,0x00,0x00,0xff))

layout = Clutter.BoxLayout()
layout.set_vertical(True)
layout.set_homogeneous(False)
layout.set_pack_start(False)

stage.set_layout_manager(layout)
stage.set_background_color(Clutter.Color.new(255, 255, 255, 255))
stage.show()

button.connect("clicked", clicked)

window.show()

Gtk.main()