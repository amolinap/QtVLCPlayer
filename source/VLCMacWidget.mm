#include "VLCMacWidget.h"
#import <Cocoa/Cocoa.h>
#include <AppKit/AppKit.h>
//#import "nsvideoview.h"
#include <QtDebug>
#include "VLCNSView.h"

VLCMacWidget::VLCMacWidget(libvlc_media_player_t *mediaPlayer, QWidget *parent) : QMacCocoaViewContainer(0, parent)
{    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    VLCVideoView *videoView = [[VLCVideoView alloc] init];
    [videoView setAutoresizingMask: NSViewHeightSizable|NSViewWidthSizable];
    this->setCocoaView(videoView);    
    libvlc_media_player_set_nsobject(mediaPlayer, this->cocoaView());

    [videoView release];
    [pool release];
}

@interface VLCOpenGLVoutView : NSView
//- (void)detachFromVout;
@end

