package de.edu.bt.vps2.calc.logik;

public class CalcLogicSoapPortTypeProxy implements de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType {
  private String _endpoint = null;
  private de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType calcLogicSoapPortType = null;
  
  public CalcLogicSoapPortTypeProxy() {
    _initCalcLogicSoapPortTypeProxy();
  }
  
  public CalcLogicSoapPortTypeProxy(String endpoint) {
    _endpoint = endpoint;
    _initCalcLogicSoapPortTypeProxy();
  }
  
  private void _initCalcLogicSoapPortTypeProxy() {
    try {
      calcLogicSoapPortType = (new de.edu.bt.vps2.calc.logik.CalcLogicSoapLocator()).getCalcLogicSoapHttpSoap11Endpoint();
      if (calcLogicSoapPortType != null) {
        if (_endpoint != null)
          ((javax.xml.rpc.Stub)calcLogicSoapPortType)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
        else
          _endpoint = (String)((javax.xml.rpc.Stub)calcLogicSoapPortType)._getProperty("javax.xml.rpc.service.endpoint.address");
      }
      
    }
    catch (javax.xml.rpc.ServiceException serviceException) {}
  }
  
  public String getEndpoint() {
    return _endpoint;
  }
  
  public void setEndpoint(String endpoint) {
    _endpoint = endpoint;
    if (calcLogicSoapPortType != null)
      ((javax.xml.rpc.Stub)calcLogicSoapPortType)._setProperty("javax.xml.rpc.service.endpoint.address", _endpoint);
    
  }
  
  public de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType getCalcLogicSoapPortType() {
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    return calcLogicSoapPortType;
  }
  
  public de.edu.bt.vps2.calc.logik.GetAktuellerWertResponse getAktuellerWert() throws java.rmi.RemoteException{
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    return calcLogicSoapPortType.getAktuellerWert();
  }
  
  public void setzeOperation(java.lang.String op) throws java.rmi.RemoteException{
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    calcLogicSoapPortType.setzeOperation(op);
  }
  
  public java.lang.String berechneErgebnis() throws java.rmi.RemoteException{
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    return calcLogicSoapPortType.berechneErgebnis();
  }
  
  public void zifferHinzu(java.lang.String ziffer) throws java.rmi.RemoteException{
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    calcLogicSoapPortType.zifferHinzu(ziffer);
  }
  
  public void reset() throws java.rmi.RemoteException{
    if (calcLogicSoapPortType == null)
      _initCalcLogicSoapPortTypeProxy();
    calcLogicSoapPortType.reset();
  }
  
  
}