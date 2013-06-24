package de.edu.bt.vps2.calc.logik;

import java.rmi.Remote;
import java.rmi.RemoteException;


public interface CalcLogic extends Remote {
	
	public String getAktuellerWert() throws RemoteException;

	public void zifferHinzu(String ziffer) throws RemoteException;

	public void setzeOperation(String op) throws RemoteException;

	/**
	 * Hier findet die eigentliche Berechnung statt!
	 */
	public String berechneErgebnis() throws RemoteException;
	
	public void reset() throws RemoteException;

}
