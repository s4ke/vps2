package de.uni.bt.vps2.compare_game.logic;

import java.rmi.RemoteException;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

public class GameLogicImpl implements GameLogic {

	private String toFind;
	private final PriorityQueue<Integer> found;
	private final Set<LogicListener> logicListeners;

	public GameLogicImpl() {
		this.toFind = "";
		this.found = new PriorityQueue<>();
		this.logicListeners = new HashSet<>();
	}

	@Override
	public String set(String string) throws RemoteException {
		this.toFind = string;
		this.found.clear();
		String forClient = this.generateForClient();
		for (LogicListener logicListener : this.logicListeners) {
			logicListener.onSet(forClient);
		}
		return forClient;
	}

	private String generateForClient() {
		StringBuilder forClient = new StringBuilder();
		for (int i = 0; i < this.toFind.length(); ++i) {
			if (this.found.contains(i)) {
				forClient.append(this.toFind.charAt(i));
			} else {
				forClient.append(".");
			}
		}
		return forClient.toString();
	}

	@Override
	public String ask(char ch) throws RemoteException {
		for (int i = 0; i < this.toFind.length(); ++i) {
			if (this.toFind.charAt(i) == ch) {
				this.found.add(i);
			}
		}
		return this.generateForClient();
	}

	@Override
	public boolean cmp(String toCompare) throws RemoteException {
		return this.toFind.equals(toCompare);
	}

	@Override
	public void addListener(LogicListener logicListener) throws RemoteException {
		this.logicListeners.add(logicListener);
	}

}
