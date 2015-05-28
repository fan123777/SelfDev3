#pragma once

class SNMP
{
public:
	SNMP();
	~SNMP();
};

// MIB (Management information base)
// SNMP protocal :
// - device
// - Agent - software running on a managed device or on a device connected to the interface controls the device
// - Network Management System (Network Management System, NMS) - software that communicates with managers to support complex data structures, reflecting the state of the network
// OID - object ID.
// Each OID is composed of two parts: a text name and SNMP address in digital form.
// SNMP operates at the application layer TCP / IP.
// The SNMP agent receives requests for UDP - 161 port.
// The manager receives a notification (Traps and InformRequests) on port 162.
// In SNMPv1 protocol specified five main units of exchange (protocol data units - PDU)
// Two PDU, GetBulkRequest and InformRequest, were introduced in SNMPv2 and transferred to SNMPv3.
// - GetRequest - The request from the manager to the object to obtain the value of a variable or list of variables.
// - SetRequest - The request from the manager to the object to the variable or variable list.
// - GetNextRequest - The request from the manager to an object to detect the available variables and their values.
// - Bypassing all the MIB agent can be produced using an iterative GetNextRequest, since OID 0.
// - GetBulkRequest - Improved version GetNextRequest. The request from the manager to the object for numerous iterations GetNextRequest.
// - Response - Returns related variables and values from the agent manager for GetRequest, SetRequest, GetNextRequest, GetBulkRequest and InformRequest.
// - Trap - Asynchronous notification from an agent - manager.
// - InformRequest - Asynchronous notification from the manager - a manager or an agent - manager.
// SNMPv2 agent may act as a proxy agent on behalf of the managed protocol SNMPv1 devices, namely:
// - Network Management System(Network management system, NMS) SNMPv2 provides commands for SNMPv1 - agent.
// - NMS sends a message SNMP - Proxy SNMPv2.
// - Proxy sends the message without changing the Get, GetNext and Set agent SNMPv1.
// - Posts GetBulk converted proxy agent posts GetNext, and then sent to the agent SNMPv1.
// - Proxy displays messages SNMPv1 trap - trap - messages in SNMPv2, and then sends them to NMS.