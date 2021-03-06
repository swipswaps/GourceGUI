/*
 The MIT License (MIT)
 Copyright (c) 2018 Lorhan Sohaky
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef CALL_BACKS_VIDEO_PAGE_H

#define CALL_BACKS_VIDEO_PAGE_H

#include <gtk/gtk.h>

void set_repository( GtkWidget *widget, gpointer data );
gboolean set_title( GtkWidget *widget, GdkEvent *event, gpointer data );
void set_screen_mode( GtkWidget *widget, gpointer data );
void set_background_color( GtkWidget *widget, gpointer data );
void set_camera_mode( GtkWidget *widget, gpointer data );

#endif
