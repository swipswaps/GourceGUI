#include <controller.h>
#include <utils.h>
#include <gource.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

_gource gource_settings;

void set_font_name(GtkFontChooser *button);
void set_font_size(GtkFontChooser *button);
void remove_size_of_font_name(char *font_name);

bool append_extension_when_necessary(GtkWidget *widget);
void string_tolower(char *string);

void free_memory(_gource *gource);

int controller (int argc, char *argv[]){
    GtkApplication *app;
    int status=0;

    init__gource(&gource_settings);
    if(is__gource_OK(&gource_settings)){
        app = gtk_application_new ("org.gourcegui", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate),NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        print_gource(&gource_settings);
        g_object_unref (app);
        free_memory(&gource_settings);
    }else{
        fprintf(stderr, "Failed to allocate memory.\n");
    }
    return status;
}

//CALLBACKs of video_page

void set_log_file(GtkWidget *widget, gpointer data){
    gource_settings.video.log_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

gboolean set_title(GtkWidget *widget, gpointer data){
    copy_string(&gource_settings.video.title,gtk_entry_get_text (GTK_ENTRY(widget)));
    if(gource_settings.video.title.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

void set_screen_mode(GtkWidget *widget, gpointer data){
    gource_settings.video.screen_mode=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widget));
}

void set_background_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    copy_string(&gource_settings.video.background_color,rgba_to_hex(rgba.red,rgba.green,rgba.blue));
    if(gource_settings.video.background_color.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}

void set_camera_mode(GtkWidget *widget, gpointer data){
    gource_settings.video.camera_mode=gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widget));
}

//CALLBACKs of subtitle_page

void set_subtitle_file(GtkWidget *widget, gpointer data){
    gource_settings.subtitle.subtitle_file=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_font(GtkWidget *widget, gpointer data){
    set_font_name(GTK_FONT_CHOOSER(widget));
    set_font_size(GTK_FONT_CHOOSER(widget));
}

gboolean set_duration(GtkWidget *widget, gpointer data){
    gource_settings.subtitle.duration=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

void set_subtitle_color(GtkWidget *widget, gpointer data){
    GdkRGBA rgba;
    gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(widget),&rgba);
    copy_string(&gource_settings.subtitle.color,rgba_to_hex(rgba.red,rgba.green,rgba.blue));
    if(gource_settings.subtitle.color.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}

//CALLBACKs other_page

gboolean set_auto_skip(GtkWidget *widget, gpointer data){
    gource_settings.other.auto_skip_seconds=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

gboolean set_seconds_per_day(GtkWidget *widget, gpointer data){
    gource_settings.other.seconds_per_day=gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
    return FALSE;
}

gboolean set_date_format(GtkWidget *widget, gpointer data){
    copy_string(&gource_settings.other.date_format,gtk_entry_get_text (GTK_ENTRY(widget)));
    if(gource_settings.other.date_format.size==0){
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
    return FALSE;
}

void set_avatar_folder(GtkWidget *widget, gpointer data){
    gource_settings.other.folder_with_users_avatar_icon=gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(widget));
}

void set_output_gource(GtkWidget *widget){
    if(append_extension_when_necessary(widget)){
        gource_settings.other.output_gorce=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widget));
    }else{
        free_memory(&gource_settings);
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(0);
    }
}



void set_font_name(GtkFontChooser *button){
    gource_settings.subtitle.font_name=gtk_font_chooser_get_font(button);
    remove_size_of_font_name(gource_settings.subtitle.font_name);
}

void set_font_size(GtkFontChooser *button){
    gource_settings.subtitle.font_size=gtk_font_chooser_get_font_size(button)/1000;
}

void remove_size_of_font_name(char *font_name){
    char *last_space=strrchr(font_name,' ');
    font_name[last_space-font_name]='\0';
}


bool append_extension_when_necessary(GtkWidget *widget){
    char *tmp=gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget));
    tmp=&tmp[strlen(tmp)-strlen(".MP4")];
    string_tolower(tmp);
    if (strcmp(tmp,".mp4")!=0) {
        tmp=(char *) malloc(sizeof(char)*(strlen(gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget)))+strlen(".mp4")));
        if(tmp!=NULL){
            sprintf(tmp,"%s.mp4", gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER(widget)));
            gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER(widget),tmp);
            free(tmp);
        }else{
            return false;
        }
    }
    return true;
}

void string_tolower(char *string){
    for(int i=0;i<strlen(string);i++){
        string[i]=tolower(string[i]);
    }
}


void free_memory(_gource *gource){
    if(gource->video.title.value!=NULL){
        free(gource->video.title.value);
    }

    if(gource->video.background_color.value!=NULL){
        free(gource->video.background_color.value);
    }

    if(gource->subtitle.color.value!=NULL){
        free(gource->subtitle.color.value);
    }

    if(gource->other.date_format.value!=NULL){
        free(gource->other.date_format.value);
    }
}
