#include <gtk/gtk.h>
#include <stdlib.h>

GtkApplication* app;

static void
on_cancel_clicked (GtkWidget* widget,
                 gpointer   data)
{
  g_print("Cancel\n");
}

static void
on_lock_clicked (GtkWidget* widget,
                 gpointer   data)
{
  g_print("Lock screen\n");
  system("slock");
}

static void
on_sleep_clicked (GtkWidget* widget,
                  gpointer   data)
{
  g_print("Going to sleep\n");
  system("slock && systemctl suspend");
}

static void
on_reboot_clicked (GtkWidget* widget,
                   gpointer   data)
{
  g_print("Rebooting\n");
  system("systemctl reboot");
}

static void
on_shutdown_clicked (GtkWidget* widget,
                   gpointer   data)
{
  g_print("Shutting down\n");
  system("systemctl poweroff");
}

GtkWidget* window;
GtkWidget* button_box;

typedef enum
{
    LOCK,
    SLEEP,
    REBOOT,
    SHUTDOWN,
    CANCEL,
    LAST_OP
} BTN_ENUM;

static guint signals[LAST_OP] = {0};

void create_button(GtkWidget* btn, const gchar* label, void (*func)(GtkWidget*, gpointer))
{
  btn = gtk_button_new_with_label (label);
  g_signal_connect (btn, "clicked", G_CALLBACK (func), NULL);
  g_signal_connect_swapped (btn, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), btn);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{

  GtkWidget* btns[LAST_OP];
  GtkWidget* empty_titlebar;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_decorated (GTK_WINDOW(window), FALSE);
  //gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

// MAKING BUTTONS
  create_button(btns[LOCK], "Lock Screen", on_lock_clicked);
  create_button(btns[SLEEP], "Sleep", on_sleep_clicked);
  create_button(btns[REBOOT], "Reboot", on_reboot_clicked);
  create_button(btns[SHUTDOWN], "Shutdown", on_shutdown_clicked);
  create_button(btns[CANCEL], "Cancel", on_cancel_clicked);

/*// SIGNAL HANDLING
  signals[SLEEP_SIGNAL] = g_signal_new_class_handler("sleep",
    G_OBJECT_CLASS_TYPE(widget_class), (GSignalFlags) (G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION),
    G_CALLBACK(on_sleep_clicked), NULL, NULL, NULL, G_TYPE_NONE, 2,
    G_TYPE_INT, G_TYPE_INT
  );
*/
  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}