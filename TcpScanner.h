#pragma once
#include "Stdafx.h"
#include "ServiceScanner.h"

/*!
 * Represents internal scan data for the TCP scanner.
 */
struct TcpScanData
{

	/*!
	 * Active non-blocking socket.
	 */
	SOCKET socket;

	/*!
	 * File descriptor set for writability.
	 */
	fd_set* fdset;

};

/*!
 * Implements an active TCP port scanner.
 * 
 * This will try to initiate the three-way handshake with all the requested services.
 * It is not a stealthy method, and does not include any trickery to bypass firewalls.
 */
class TcpScanner : public ServiceScanner
{
public:
	
	/*!
	 * Number of milliseconds to wait for connections to finish.
	 */
	unsigned long timeout = 1000;

	/*!
	 * Indicates whether to wait for and grab service banners.
	 */
	bool grabBanner = true;

	/*!
	 * Indicates whether to run protocol-tailored scripts.
	 */
	bool runScripts = true;

	/*!
	 * Scans a service to determine aliveness.
	 * 
	 * \param service Service.
	 */
	void Scan(Service* service) override;

	/*!
	 * Scans a list of services to determine aliveness.
	 * 
	 * \param services List of services.
	 */
	void Scan(Services* services) override;

	/*!
	 * Frees up the resources allocated during the lifetime of this instance.
	 */
	~TcpScanner() override;

private:

	/*!
	 * Initializes the sockets and starts the non-blocking connection.
	 *
	 * \param service Service.
	 */
	void initSocket(Service* service);

	/*!
	 * Collects the results of the socket connections.
	 *
	 * \param service Service.
	 * \param last Whether this is the last iteration.
	 */
	void pollSocket(Service* service, bool last = false);

	/*!
	 * Reads the banner from the specified service.
	 * This requires that the service have a connected socket.
	 *
	 * \param service Service.
	 * \param last Whether this is the last iteration.
	 */
	void readBanner(Service* service, bool last = false);

};