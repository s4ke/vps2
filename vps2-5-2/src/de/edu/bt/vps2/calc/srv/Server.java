package de.edu.bt.vps2.calc.srv;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RemoteServer;
import java.rmi.server.UnicastRemoteObject;

import de.edu.bt.vps2.calc.logik.CalcLogic;
import de.edu.bt.vps2.calc.logik.CalcLogicImpl;

public class Server {

	//Die Server-Klasse hat hier nur eine einfache Hauptmethode
	//Eventuell geworfene Exceptions werden an die Hauptmethode angehängt
	public static void main(String[] args) throws RemoteException {
		//Zuerst starten wir die RMI-Registrierung
		Registry reg = LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
		//Exportieren des tatsächlichen Objekts zum Interface
		CalcLogic stub = (CalcLogic) UnicastRemoteObject
				.exportObject(new CalcLogicImpl(), 0);
		//Bekannt machen unseres Objekts bei der Registrierung
		reg.rebind("Calculator", stub);
		//Anzeigen der registrierung (des Objekts)
		System.out.println(reg);
		//Anzeigen sämtlicher Server-Ausgaben auf der Kommandozeile
		RemoteServer.setLog(System.out);
	}
}
