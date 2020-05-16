.. NOTE(stephenfin): If making changes to this file, ensure that the
   start-after/end-before lines found in 'Documentation/intro/what-is-ovs'
   are kept up-to-date.

============
Open vSwitch
============


What is Open vSwitch?
---------------------

Open vSwitch is a multilayer software switch.

Open vSwitch is well suited to function as a virtual switch in VM environments.
In addition to exposing standard control and visibility interfaces to the
virtual networking layer, it was designed to support distribution across
multiple physical servers.  Open vSwitch supports multiple Linux-based
virtualization technologies including Xen/XenServer, KVM, and VirtualBox.

You can read for more information here: https://github.com/openvswitch/ovs/blob/master/README.rst

What we do here:
------------
Extend OvS function to support anomaly detection in our project, which is about detecting DDoS attack in SDN network.
This work includes:<br/>
- Monitor several traffic features<br/>
- Detect the anomalies by anomaly detection algorithm (Local Outlier Factor/Local Outlier Probabilities)<br/>
- Create a new OpenFlow message to notify SDN Controller<br/>

