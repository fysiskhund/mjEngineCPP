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
    resourceManager = new mjResourceManager(pathPrefix);
    setupGame(self.view.bounds.size.width, self.view.bounds.size.height, resourceManager);

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

@end
