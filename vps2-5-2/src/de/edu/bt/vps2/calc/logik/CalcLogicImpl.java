package de.edu.bt.vps2.calc.logik;

import java.rmi.RemoteException;

public class CalcLogicImpl implements CalcLogic {
	
	private String aktuellerWert;
	private String gespeicherterWert;
	private String operation;

	public CalcLogicImpl() {
		aktuellerWert = "0";
		gespeicherterWert = "0";
		operation = "";
	}

	@Override
	public String getAktuellerWert() {
		return aktuellerWert;
	}

	@Override
	public void zifferHinzu(String ziffer) {
		aktuellerWert = aktuellerWert + ziffer;
	}

	@Override
	public void setzeOperation(String op) {
		operation = op;
		gespeicherterWert = aktuellerWert;
		aktuellerWert = new String();
	}

	/*
	 * Hier findet die eigentliche Berechnung statt!
	 * Die Operanden und die Operation wurden schon eingegeben.
	 * Die eigentliche Berechnung wird durch die Methoden
	 * add() sub() mult() und div() erledigt.  
	 */
	@Override
	public String berechneErgebnis() {
		Integer a = Integer.parseInt(gespeicherterWert);
		Integer b = Integer.parseInt(aktuellerWert);
		Integer ergebnis;
		if (operation.equals("+"))
			ergebnis = add(a, b);
		else if (operation.equals("-"))
			ergebnis = sub(a, b);
		else if (operation.equals("x"))
			ergebnis = mult(a, b);
		else if (operation.equals(":"))
			ergebnis = div(a, b);
		else
			return "ERROR";
		aktuellerWert = ergebnis.toString();
		return ergebnis.toString();
	}

	private Integer div(Integer a, Integer b) {
		return a / b;
	}

	private Integer mult(Integer a, Integer b) {
		return a * b;
	}

	private Integer sub(Integer a, Integer b) {
		return a - b;
	}

	private Integer add(Integer a, Integer b) {
		return a + b;
	}

	@Override
	public void reset() throws RemoteException {
		this.aktuellerWert = "0";
		this.gespeicherterWert = "0";
		this.operation = "0";
	}

}
