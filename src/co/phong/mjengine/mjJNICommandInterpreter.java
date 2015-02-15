package co.phong.mjengine;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.net.Uri;
import android.os.Environment;

public class mjJNICommandInterpreter {
	
	public static MediaPlayer musicPlayer = new MediaPlayer();
	
	public static SoundPool soundPool = new SoundPool(16, AudioManager.STREAM_MUSIC, 0);
	
	public static ArrayList<Integer> soundIDs = new ArrayList<Integer>();
	
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
				
				//instructions for the soundPool (aka sound effects)
				case 51:
					soundIDs.add(soundPool.load(cmdAndArg[1], 1));
					break;
				case 52:
					
					soundPool.play(soundIDs.get(Integer.parseInt(cmdAndArg[1])).intValue(), Float.parseFloat(cmdAndArg[2]), Float.parseFloat(cmdAndArg[3]), 
							Integer.parseInt(cmdAndArg[4]), Integer.parseInt(cmdAndArg[5]), Float.parseFloat(cmdAndArg[6]));
				case 53:
					soundPool.pause(Integer.parseInt(cmdAndArg[1]));
					break;
				case 54:
					soundPool.stop(Integer.parseInt(cmdAndArg[1]));
					break;
				default:
					break;
				}
				
			}
	}
}
