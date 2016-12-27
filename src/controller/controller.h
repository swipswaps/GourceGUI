#include <main_menu.h>
#include <gtk/gtk.h>
#include <gource.h>

int controller (int argc, char *argv[]);
void set_log_file(GtkWidget *widget, gpointer data);
void set_title(GtkWidget *widget, gpointer data);
void set_screen_mode(GtkWidget *widget, gpointer data);
void set_background_color(GtkWidget *widget, gpointer data);
void set_camera_mode(GtkWidget *widget, gpointer data);