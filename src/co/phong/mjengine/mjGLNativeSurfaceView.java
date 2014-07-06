package co.phong.mjengine;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class mjGLNativeSurfaceView extends GLSurfaceView{

	public mjGLNativeSurfaceView(Context context, AttributeSet attrs) {
		super(context, attrs);
		mjRenderer renderer = new mjRenderer();
		renderer.Init(context);
		this.setRenderer(renderer);
	}

}
