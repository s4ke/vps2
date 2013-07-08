package de.uni.bt.vps2.compare_game.logic;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface LogicListener extends Remote {
	
	public void onSet(String value) throws RemoteException;
	
}