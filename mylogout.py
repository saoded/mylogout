import os
import gi

gi.require_version('Gtk', '3.0')
gi.require_version('Keybinder', '3.0')

from gi.repository import Gtk
from gi.repository import Keybinder

def bind_accelerator(accelerators, widget, accelerator, signal='clicked'):
    key, mod = Gtk.accelerator_parse(accelerator)
    widget.add_accelerator(signal, accelerators, key, mod, Gtk.AccelFlags.VISIBLE)

class ButtonWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="logout")
        self.set_border_width(10)
        self.set_position(Gtk.WindowPosition.CENTER)
        if not self.is_composited():
            print("Transparency feature unavailable")
        else:
            self.set_opacity(0)
        self.set_decorated(False)


        vbox = Gtk.Box(spacing=6, orientation=Gtk.Orientation.VERTICAL)
        self.add(vbox)

        self.lock_btn = Gtk.Button.new_with_mnemonic("Loc_k")
        self.lock_btn.connect("clicked", self.on_lock_clicked)
        vbox.pack_start(self.lock_btn, True, True, 0)

        self.sleep_btn = Gtk.Button.new_with_mnemonic("_Sleep")
        self.sleep_btn.connect("clicked", self.on_sleep_clicked)
        vbox.pack_start(self.sleep_btn, True, True, 0)

        self.restart_btn = Gtk.Button.new_with_mnemonic("_Restart")
        self.restart_btn.connect("clicked", self.on_restart_clicked)
        vbox.pack_start(self.restart_btn, True, True, 0)

        self.shutdown_btn = Gtk.Button.new_with_mnemonic("Sh_utdown")
        self.shutdown_btn.connect("clicked", self.on_shutdown_clicked)
        vbox.pack_start(self.shutdown_btn, True, True, 0)

        self.cancel_btn = Gtk.Button.new_with_mnemonic("_Cancel")
        self.cancel_btn.connect("clicked", self.on_cancel_clicked)
        vbox.pack_start(self.cancel_btn, True, True, 0)


    def on_sleep_clicked(self, button):
        print("Going to sleep")
        Gtk.main_quit()
        os.system("systemctl suspend && slock")

    def on_lock_clicked(self, button):
        print("Lock screen")
        Gtk.main_quit()
        os.system("slock")

    def on_shutdown_clicked(self, button):
        print("Shutting down")
        Gtk.main_quit()
        os.system("systemctl poweroff")

    def on_restart_clicked(self, button):
        print("Rebooting")
        Gtk.main_quit()
        os.system("systemctl reboot")

    def on_cancel_clicked(self, button):
        print("Operation cancelled")
        Gtk.main_quit()

win = ButtonWindow()

Keybinder.init()
Keybinder.bind('Escape', win.on_cancel_clicked)
Keybinder.bind('c', win.on_cancel_clicked)
Keybinder.bind('k', win.on_lock_clicked)
Keybinder.bind('l', win.on_lock_clicked)
Keybinder.bind('s', win.on_sleep_clicked)
Keybinder.bind('r', win.on_restart_clicked)
Keybinder.bind('u', win.on_shutdown_clicked)

win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
