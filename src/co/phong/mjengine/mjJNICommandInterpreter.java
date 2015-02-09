package co.phong.mjengine;

import java.io.File;
import java.io.IOException;

import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Environment;

public class mjJNICommandInterpreter {
	
	public static MediaPlayer musicPlayer = new MediaPlayer();
	
	public static void ParseCommands(String commandsFromJNI, Context androidContext)
	{
			String[] lines = commandsFromJNI.split("\n");
			for(String line:lines)
			{
				String[] cmdAndArg = line.split(":");
				int cmd = Integer.parseInt(cmdAndArg[0]);
				
				switch(cmd)
				{
				case 1:
					

					//Uri fileUri = Uri.parse(Environment.getExternalStorageDirectory().getPath()+cmdAndArg[1]);
					try {
						musicPlayer.setDataSource(cmdAndArg[1]);
						musicPlayer.prepare();
					} catch (IllegalArgumentException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (SecurityException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IllegalStateException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					musicPlayer.start();
					break;
				case 2:
					musicPlayer.start();
					break;
				case 3:
					musicPlayer.pause();
					break;
				case 4:
					musicPlayer.stop();
					break;
				default:
					break;
				}
				
			}
	}
}
