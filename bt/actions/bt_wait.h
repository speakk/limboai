/* bt_wait.h */

#ifndef BT_WAIT_H
#define BT_WAIT_H

#include "bt_action.h"
#include "core/object/object.h"

class BTWait : public BTAction {
	GDCLASS(BTWait, BTAction);

private:
	double duration = 1.0;

	double time_passed = 0.0;

protected:
	static void _bind_methods();

	virtual String _generate_name() const override;
	virtual void _enter() override;
	virtual int _tick(double p_delta) override;

public:
	void set_duration(double p_value) {
		duration = p_value;
		emit_changed();
	}
	double get_duration() const { return duration; }
};

#endif // BT_WAIT_H