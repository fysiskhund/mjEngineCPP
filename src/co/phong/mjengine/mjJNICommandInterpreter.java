package co.phong.mjengine;

import java.io.File;

import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;

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
					File f = new File(cmdAndArg[1]);
					
					musicPlayer = MediaPlayer.create(androidContext, f.toURI());
					//MusicPlayer::LoadMusic
					break;
				case 2:
					//MusicPlayer::PlayMusic
					break;
				default:
					break;
				}
				
			}
	}
}
