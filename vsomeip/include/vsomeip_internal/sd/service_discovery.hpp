//
// service_discovery.hpp
//
// This file is part of the BMW Some/IP implementation.
//
// Copyright ������ 2013, 2014 Bayerische Motoren Werke AG (BMW).
// All rights reserved.
//

#ifndef VSOMEIP_INTERNAL_SD_SERVICE_DISCOVERY_HPP
#define VSOMEIP_INTERNAL_SD_SERVICE_DISCOVERY_HPP

#include <boost/asio/io_service.hpp>

#include <vsomeip/primitive_types.hpp>

namespace vsomeip {

class daemon;
class endpoint;
class message_base;

namespace sd {

namespace client_state_machine {
	struct machine;
} // namespace client_state_machine

typedef struct client_state_machine::machine client_state_machine_t;

namespace service_state_machine {
	struct machine;
} // namespace service_state_machine

typedef struct service_state_machine::machine service_state_machine_t;

class service_discovery {
public:
	virtual ~service_discovery() {};

	virtual boost::asio::io_service & get_service() = 0;

	virtual daemon * get_owner() const = 0;
	virtual void set_owner(daemon *_owner) = 0;

	virtual void init() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void on_provide_service(service_id _service, instance_id _instance) = 0;
	virtual void on_withdraw_service(service_id _service, instance_id _instance) = 0;

	virtual void on_start_service(service_id _service, instance_id _instance) = 0;
	virtual void on_stop_service(service_id _service, instance_id _instance) = 0;

	virtual void on_request_service(service_id _service, instance_id _instance) = 0;
	virtual void on_release_service(service_id _service, instance_id _instance) = 0;

	virtual void on_message(const uint8_t *_data, uint32_t _size,
							const endpoint *_source, const endpoint *_target) = 0;

	virtual bool send_find_service(client_state_machine_t *_data) = 0;
	virtual bool send_offer_service(service_state_machine_t *_data, const endpoint *_target) = 0;
	virtual bool send_stop_offer_service(service_state_machine_t *_data) = 0;
};

} // sd
} // namespace vsomeip

#endif // VSOMEIP_INTERNAL_SD_SERVICE_DISCOVERY_HPP