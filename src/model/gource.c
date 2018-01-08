/*
The MIT License (MIT)
Copyright (c) 2016 Lorhan Sohaky
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

#include "gource.h"
#include "dstring.h"
#include <stdio.h>

static void init_video_with_default_values( Video *video );
static void init_caption_with_default_values( Caption *caption );
static void init_other_with_default_values( Other *other );

static int is_video_ok( Video *video );
static int is_caption_ok( Caption *caption );
static int is_other_ok( Other *other );

static void free_video( Video *video );
static void free_caption( Caption *caption );
static void free_other( Other *other );

void init_string( String **destination, const char *initial_value );
bool is_malloc_OK( Gource *gource );

void init_gource_with_default_values( Gource *gource ) {
    init_video_with_default_values( &gource->video );
    init_caption_with_default_values( &gource->caption );
    init_other_with_default_values( &gource->other );
}

void init_video_with_default_values( Video *video ) {
    video->repository = string_new_with_text( DEFAULT_REPOSITORY );
    video->title = string_new_with_text( DEFAULT_TITLE );
    video->screen_mode = string_new_with_text( DEFAULT_SCREEN_MODE );
    video->background_color = string_new_with_text( DEFAULT_BACKGROUND_COLOR );
    video->camera_mode = string_new_with_text( DEFAULT_CAMERA_MODE );
}

void init_caption_with_default_values( Caption *caption ) {
    caption->file = string_new_with_text( DEFAULT_CAPTION_FILE );
    caption->font_size = string_new_with_text( DEFAULT_CAPTION_FONT_SIZE );
    caption->duration = string_new_with_text( DEFAULT_CAPTION_DURATION );
    caption->color = string_new_with_text( DEFAULT_CAPTION_COLOR );
}

void init_other_with_default_values( Other *other ) {
    other->auto_skip_seconds = string_new_with_text( DEFAULT_AUTO_SKIP_SECONDS );
    other->seconds_per_day = string_new_with_text( DEFAULT_SECONDS_PER_DAY );
    other->date_format = string_new_with_text( DEFAULT_DATE_FORMAT );
    other->folder_with_users_avatar_icon =
        string_new_with_text( DEFAULT_FOLDER_WITH_USERS_AVATAR_ICON );
    other->output_gorce = string_new_with_text( DEFAULT_OUTPUT_GOURCE );
}

int is_gource_ok( Gource *gource ) {
    return is_video_ok( &gource->video ) && is_caption_ok( &gource->caption ) &&
        is_other_ok( &gource->other );
}

static int is_video_ok( Video *video ) {
    return video->repository && video->title && video->screen_mode && video->background_color &&
        video->camera_mode;
}

static int is_caption_ok( Caption *caption ) {
    return caption->file && caption->font_size && caption->duration && caption->color;
}

static int is_other_ok( Other *other ) {
    return other->auto_skip_seconds && other->seconds_per_day && other->date_format &&
        other->folder_with_users_avatar_icon && other->output_gorce;
}

void print_gource( Gource *gource ) {
    printf( "Video:\n" );
    printf( "\tRepository - %s\n", string_get_text( gource->video.repository ) );
    printf( "\tTitle - %s\n", string_get_text( gource->video.title ) );
    printf( "\tScreen Mode - %s\n", string_get_text( gource->video.screen_mode ) );
    printf( "\tBackground color - %s\n", string_get_text( gource->video.background_color ) );
    printf( "\tCamer mode - %s\n", string_get_text( gource->video.camera_mode ) );

    printf( "caption:\n" );
    printf( "\tcaption file - %s\n", string_get_text( gource->caption.file ) );
    printf( "\tFont size - %s\n", string_get_text( gource->caption.font_size ) );
    printf( "\tDuration - %s\n", string_get_text( gource->caption.duration ) );
    printf( "\tColor - %s\n", string_get_text( gource->caption.color ) );

    printf( "Other:\n" );
    printf( "\tAuto Skip seconds - %s\n", string_get_text( gource->other.auto_skip_seconds ) );
    printf( "\tSeconds per day - %s\n", string_get_text( gource->other.seconds_per_day ) );
    printf( "\tDate format - %s\n", string_get_text( gource->other.date_format ) );
    printf( "\tFolder with users avatar icon - %s\n",
            string_get_text( gource->other.folder_with_users_avatar_icon ) );
    printf( "\tOutput gource - %s\n", string_get_text( gource->other.output_gorce ) );
}

void free_gource( Gource *gource ) {
    free_video( &gource->video );
    free_caption( &gource->caption );
    free_other( &gource->other );
}

static void free_video( Video *video ) {
    if( video->repository ) {
        string_free( video->repository );
    }

    if( video->title ) {
        string_free( video->title );
    }

    if( video->screen_mode ) {
        string_free( video->screen_mode );
    }

    if( video->background_color ) {
        string_free( video->background_color );
    }

    if( video->camera_mode ) {
        string_free( video->camera_mode );
    }
}

static void free_caption( Caption *caption ) {
    if( caption->file ) {
        string_free( caption->file );
    }

    if( caption->font_size ) {
        string_free( caption->font_size );
    }

    if( caption->duration ) {
        string_free( caption->duration );
    }

    if( caption->color ) {
        string_free( caption->color );
    }
}

static void free_other( Other *other ) {
    if( other->auto_skip_seconds ) {
        string_free( other->auto_skip_seconds );
    }

    if( other->seconds_per_day ) {
        string_free( other->seconds_per_day );
    }

    if( other->date_format ) {
        string_free( other->date_format );
    }

    if( other->folder_with_users_avatar_icon ) {
        string_free( other->folder_with_users_avatar_icon );
    }

    if( other->output_gorce ) {
        string_free( other->output_gorce );
    }
}
