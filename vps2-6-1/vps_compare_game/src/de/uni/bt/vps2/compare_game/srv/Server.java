package de.uni.bt.vps2.compare_game.srv;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RemoteServer;
import java.rmi.server.UnicastRemoteObject;

import de.uni.bt.vps2.compare_game.logic.GameLogic;
import de.uni.bt.vps2.compare_game.logic.GameLogicImpl;

public class Server {

	//Die Server-Klasse hat hier nur eine einfache Hauptmethode
	//Eventuell geworfene Exceptions werden an die Hauptmethode angehängt
	public static void main(String[] args) throws RemoteException {
		//Zuerst starten wir die RMI-Registrierung
		Registry reg = LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
		//Exportieren des tatsächlichen Objekts zum Interface
		GameLogic stub = (GameLogic) UnicastRemoteObject
				.exportObject(new GameLogicImpl(), 0);
		//Bekannt machen unseres Objekts bei der Registrierung
		reg.rebind("GameLogic", stub);
		reg.rebind("rmi", reg);
		//Anzeigen dher registrierung (des Objekts)
		System.out.println(reg);
		//Anzeigen sämtlicher Server-Ausgaben auf der Kommandozeile
		RemoteServer.setLog(System.out);
	}
}
