/**
 * 
 */
package edu.umn.cs.crisys.smaccm.aadl2rtos.model.thread;

import java.util.HashSet;
import java.util.Set;

import edu.umn.cs.crisys.smaccm.aadl2rtos.model.type.Type;

/**
 * @author Whalen
 *
 * This class represents a shared data object in AADL.
 */
public class SharedData {

  private String portName;
  private Type dataType = null;
  private ThreadImplementation camkesOwner;
  private Set<SharedDataAccessor> accessors;
  
  public SharedData(String portName, Type dataType) {
    accessors = new HashSet<SharedDataAccessor>();
    this.portName = portName;
    this.dataType = dataType;
  }
  
  public String getPortName() {
    return this.portName;
  }
  
  public Set<SharedDataAccessor> getAccessors() {
    return accessors;
  }

  public void setAccessors(Set<SharedDataAccessor> accessors) {
    this.accessors = accessors;
  }
  
  public void addAccessor(SharedDataAccessor acc) {
    this.accessors.add(acc);
  }

  public String getMutexName() {
     return ("mutex_" + getPortName()).toLowerCase() ; 
  }

  public String getMutexDefine() {
    return ("MUTEX_ID_" + getMutexName()).toUpperCase();
  }
  
  
  public String getVarName() {
    return "var_" + getPortName(); 
  }
  
  public Type getType() {
    return this.dataType;
  }

  public ThreadImplementation getCamkesOwner() {
    return camkesOwner;
  }

  public void setCamkesOwner(ThreadImplementation camkesOwner) {
    this.camkesOwner = camkesOwner;
  }

  
}
