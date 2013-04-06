from gi.repository import Gtk, Clutter, GtkClutter
import random

def clicked(event):
    actor = Clutter.Actor()
    actor.set_size(100, 100)
    actor.set_y_align(Clutter.ActorAlign.FILL)
    actor.set_x_align(Clutter.ActorAlign.FILL)
    actor.set_background_color(Clutter.Color.new(random.randint(0,255),
        random.randint(0,255), random.randint(0,255),255))
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