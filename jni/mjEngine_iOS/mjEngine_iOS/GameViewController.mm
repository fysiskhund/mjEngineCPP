//
//  GameViewController.m
//  mjEngine_iOS
//
//  Created by alejandro on 23/08/2016.
//  Copyright © 2016 Phong-Shaded Hallucinations. All rights reserved.
//

#import "GameViewController.h"



using namespace mjEngine;


@interface GameViewController () {

    mjResourceManager* resourceManager;
    
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end

@implementation GameViewController

- (void)viewDidLoad
{
    self.preferredFramesPerSecond = 60;
    
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
}

- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)setupGL
{

    
    [EAGLContext setCurrentContext:self.context];

    // Most glEnabling stuff is done by mjEngine.
    std::string pathPrefix = "mjEngineCPP";
    setupGame(self.view.bounds.size.width, self.view.bounds.size.height, pathPrefix);

}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    

    
    self.effect = nil;
    
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    
    
    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    
    renderFrame(self.timeSinceLastUpdate);

}

- (void) touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    
    UITouch *aTouch = [touches anyObject];
    
    CGPoint point = [aTouch locationInView:self.view];
    
    printf("Touchy touchy at %f, %f !!\n", point.x, point.y);
    
    //FIXME: find out how to get which finger is being tracked. i.e. fingerID
    // This might help https://github.com/mattgemmell/TouchTest/blob/master/Classes/MGTrackingView.m
    // Apparently each "touch" event always has the same memory address.
    // Would be easier with a number, but then it wouldn't be Apple, would it?
    
    TouchEvent(0, (int) point.x, (int) point.y, true);
}

- (void) touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    
}

- (void) touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *aTouch = [touches anyObject];
    
    CGPoint point = [aTouch locationInView:self.view];
    
    TouchEvent(0, (int) point.x, (int) point.y, false);
}

- (void) touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    
}



@end
