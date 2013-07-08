package de.uni.bt.vps2.compare_game.logic;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface GameLogic extends Remote {

	public String set(String string) throws RemoteException;
	
	public String ask(char ch) throws RemoteException;
	
	public boolean cmp(String toCompare) throws RemoteException;
	
	public void addListener(LogicListener logicListener) throws RemoteException;
	
}
