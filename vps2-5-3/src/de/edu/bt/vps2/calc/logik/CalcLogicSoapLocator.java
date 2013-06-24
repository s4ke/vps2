/**
 * CalcLogicSoapLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package de.edu.bt.vps2.calc.logik;

public class CalcLogicSoapLocator extends org.apache.axis.client.Service implements de.edu.bt.vps2.calc.logik.CalcLogicSoap {

    public CalcLogicSoapLocator() {
    }


    public CalcLogicSoapLocator(org.apache.axis.EngineConfiguration config) {
        super(config);
    }

    public CalcLogicSoapLocator(java.lang.String wsdlLoc, javax.xml.namespace.QName sName) throws javax.xml.rpc.ServiceException {
        super(wsdlLoc, sName);
    }

    // Use to get a proxy class for CalcLogicSoapHttpSoap11Endpoint
    private java.lang.String CalcLogicSoapHttpSoap11Endpoint_address = "http://192.168.0.14:8080/vps_5_3_new/services/CalcLogicSoap.CalcLogicSoapHttpSoap11Endpoint/";

    public java.lang.String getCalcLogicSoapHttpSoap11EndpointAddress() {
        return CalcLogicSoapHttpSoap11Endpoint_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String CalcLogicSoapHttpSoap11EndpointWSDDServiceName = "CalcLogicSoapHttpSoap11Endpoint";

    public java.lang.String getCalcLogicSoapHttpSoap11EndpointWSDDServiceName() {
        return CalcLogicSoapHttpSoap11EndpointWSDDServiceName;
    }

    public void setCalcLogicSoapHttpSoap11EndpointWSDDServiceName(java.lang.String name) {
        CalcLogicSoapHttpSoap11EndpointWSDDServiceName = name;
    }

    public de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType getCalcLogicSoapHttpSoap11Endpoint() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(CalcLogicSoapHttpSoap11Endpoint_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getCalcLogicSoapHttpSoap11Endpoint(endpoint);
    }

    public de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType getCalcLogicSoapHttpSoap11Endpoint(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            de.edu.bt.vps2.calc.logik.CalcLogicSoapSoap11BindingStub _stub = new de.edu.bt.vps2.calc.logik.CalcLogicSoapSoap11BindingStub(portAddress, this);
            _stub.setPortName(getCalcLogicSoapHttpSoap11EndpointWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setCalcLogicSoapHttpSoap11EndpointEndpointAddress(java.lang.String address) {
        CalcLogicSoapHttpSoap11Endpoint_address = address;
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (de.edu.bt.vps2.calc.logik.CalcLogicSoapPortType.class.isAssignableFrom(serviceEndpointInterface)) {
                de.edu.bt.vps2.calc.logik.CalcLogicSoapSoap11BindingStub _stub = new de.edu.bt.vps2.calc.logik.CalcLogicSoapSoap11BindingStub(new java.net.URL(CalcLogicSoapHttpSoap11Endpoint_address), this);
                _stub.setPortName(getCalcLogicSoapHttpSoap11EndpointWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        java.lang.String inputPortName = portName.getLocalPart();
        if ("CalcLogicSoapHttpSoap11Endpoint".equals(inputPortName)) {
            return getCalcLogicSoapHttpSoap11Endpoint();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://logik.calc.vps2.bt.edu.de", "CalcLogicSoap");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("http://logik.calc.vps2.bt.edu.de", "CalcLogicSoapHttpSoap11Endpoint"));
        }
        return ports.iterator();
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(java.lang.String portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        
if ("CalcLogicSoapHttpSoap11Endpoint".equals(portName)) {
            setCalcLogicSoapHttpSoap11EndpointEndpointAddress(address);
        }
        else 
{ // Unknown Port Name
            throw new javax.xml.rpc.ServiceException(" Cannot set Endpoint Address for Unknown Port" + portName);
        }
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(javax.xml.namespace.QName portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        setEndpointAddress(portName.getLocalPart(), address);
    }

}
