package co.phong.mjengine;

import java.io.File;

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
					if (musicPlayer != null)
					{
						musicPlayer.release();
						musicPlayer = null;
					}

					
					musicPlayer = MediaPlayer.create(androidContext, Uri.parse(Environment.getExternalStorageDirectory().getPath()+cmdAndArg[1]));
					//MusicPlayer::LoadMusic
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
