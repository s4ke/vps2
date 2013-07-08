package de.uni.bt.vps2.compare_game.client;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

import de.uni.bt.vps2.compare_game.logic.GameLogic;
import de.uni.bt.vps2.compare_game.logic.LogicListener;

public class Client {

	public static void main(String[] args) throws RemoteException,
			NotBoundException {
		LogicListener listener = new LogicListener() {

			@Override
			public void onSet(String value) throws RemoteException {
				System.out.println("Set on Server: " + value);
			}

		};
		UnicastRemoteObject.exportObject(listener, 0);
		// Zuerst verbinden wir zur Registry des entfernten RMI-Servers
		Registry reg = LocateRegistry.getRegistry("127.0.0.1",
				Registry.REGISTRY_PORT);
		// Anfragen eines "Calculator"-Objekts beim RMI-Server
		GameLogic calc = (GameLogic) reg.lookup("GameLogic");
		calc.addListener(listener);
		calc.set("Toast");
		int length = 0;
		// will never close ;)
		try (Scanner sc = new Scanner(System.in)) {
			String input = null;
			boolean correct = true;
			while (!(input = sc.nextLine()).equals("")) {
				if (correct) {
					length = calc.set(input).length();
					correct = false;
				} else {
					if (input.length() == 1 && input.length() != length) {
						System.out.println(calc.ask(input.charAt(0)));
					} else {
						correct = calc.cmp(input);
						if(correct) {
							System.out.println("correct.");
						} else {
							System.out.println("wrong.");
						}
					}
				}
			}
		}
	}

}
