# Event Log Applications
## Summary
The Event Log is Syslog Server that is optimized for receiving logs and events from applications.  
The Event Log is based upon the Syslog protocol ([RFC5424](https://www.rfc-editor.org/rfc/rfc5424)). 
Traditionally is the protocol used to get log events from communication devices and databases but
the Event Log applications extends its use for other applications.

The repository doesn't include any libraries. Instead it consist of the following applications.
- **Event Log Service/Daemon**. This implements the server. 
    It is intended to run as a service on Windows and as a daemon on Unix/Linux based operating systems..
- **Event Log Explorer**. A desktop GUI application that show the events.
- **Service Daemon**. Windows service that start and supervise other executables (daemons).
- **Service Explorer**. Support GUI for configure Windows service daemons.
- **Listen Daemon**. Simple daemon executable that supervise listen servers.
- **Listen Viewer**. GUI application that show listen messages.
- **Workflow Explorer**. GUI application that configure workflow servers as the event log server.
- **ODS Configurator**. GUI application that configure and creates ODS databases.

## Installation
Installation kit for Windows (TBD):
[Event Log v1.0.0](https://github.com/ihedvall/eventlib/releases/download/v1.0.0/eventlogexe).

## Documentation 
The documentation can be found on GitHub Pages (TBD): 
[Event Log](https://ihedvall.github.io/eventlog)

## Building
The applications can be built but it requires a lot of third-party libraries. Use the pre-built install kits instead. 
The project uses CMAKE for building. The following third-party libraries are used:

- Boost Library. Set the 'Boost_ROOT' variable to the Boost root path.
- UtilLib Library. Fetched by cmake but uses other libraries [UtilLib](https://github.com/ihedvall/utillib).
- WorkflowLib Library. Fetched by cmake but uses other libraries [WorkflowlLib](https://github.com/ihedvall/workflowlib).
- MdfLib Library. Fetched by cmake but uses other libraries [MdfLib](https://github.com/ihedvall/mdflib).
- OdsLib Library. Fetched by cmake but uses other libraries [OdsLib](https://github.com/ihedvall/odslib).
- WxWidgets Library. Is required if the GUI applications should be built.

## License

The project uses the MIT license. See external LICENSE file in project root.

