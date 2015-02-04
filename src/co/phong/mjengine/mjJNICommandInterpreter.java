package co.phong.mjengine;

import android.media.MediaPlayer;
import android.net.Uri;

public class mjJNICommandInterpreter {
	
	public static MediaPlayer musicPlayer = new MediaPlayer();
	
	public static void ParseCommands(String commandsFromJNI)
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
					//musicPlayer = MediaPlayer.create(androidContextm, Uri(cmdAndArg[1]));
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
