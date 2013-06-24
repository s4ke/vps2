/**
 * CalcLogicSoapPortType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package de.edu.bt.vps2.calc.logik;

public interface CalcLogicSoapPortType extends java.rmi.Remote {
    public de.edu.bt.vps2.calc.logik.GetAktuellerWertResponse getAktuellerWert() throws java.rmi.RemoteException;
    public void setzeOperation(java.lang.String op) throws java.rmi.RemoteException;
    public java.lang.String berechneErgebnis() throws java.rmi.RemoteException;
    public void zifferHinzu(java.lang.String ziffer) throws java.rmi.RemoteException;
    public void reset() throws java.rmi.RemoteException;
}
