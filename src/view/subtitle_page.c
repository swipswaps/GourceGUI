#include <subtitle_page.h>

GtkWidget *init_subtitle_page(GtkWidget *window){
    GtkWidget *grid,*widget;
    GtkListStore *liststore;
    GtkCellRenderer *column;
    GdkRGBA rgba;
    grid=gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_row_homogeneous (GTK_GRID(grid),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(grid),10);

    widget=gtk_label_new("Subtitle file: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,0,1,1);

    widget=gtk_file_chooser_button_new ("Choose a LOG file",GTK_FILE_CHOOSER_ACTION_OPEN);
    gtk_grid_attach(GTK_GRID(grid),widget,1,0,1,1);

    widget=gtk_label_new("Font: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,1,1,1);

    widget=gtk_font_button_new ();
    gtk_grid_attach(GTK_GRID(grid),widget,1,1,1,1);

    widget=gtk_label_new("Duration: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,2,1,1);

    widget=gtk_spin_button_new_with_range(0,100,1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget),3);//I tested, so 3 it's a good number (LOL)
    gtk_grid_attach(GTK_GRID(grid),widget,1,2,1,1);

    widget=gtk_label_new("Color: ");
    gtk_grid_attach(GTK_GRID(grid),widget,0,3,1,1);

    gdk_rgba_parse(&rgba,"#FFD700");//Set default color
    widget=gtk_color_button_new_with_rgba(&rgba);
    gtk_color_button_set_title (GTK_COLOR_BUTTON(widget),"Choose a color for the subtitle");
    gtk_grid_attach(GTK_GRID(grid),widget,1,3,1,1);

    return grid;
}