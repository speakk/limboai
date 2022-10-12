/* limbo_hsm.h */

#ifndef LIMBO_HSM_H
#define LIMBO_HSM_H

#include "core/object.h"
#include "limbo_state.h"

class LimboHSM : public LimboState {
	GDCLASS(LimboHSM, LimboState);

public:
	enum UpdateMode : unsigned int {
		IDLE, // automatically call update() during NOTIFICATION_PROCESS
		PHYSICS, // automatically call update() during NOTIFICATION_PHYSICS
		MANUAL, // manually update state machine: user must call update(delta)
	};

private:
	UpdateMode update_mode;
	LimboState *initial_state;
	LimboState *active_state;
	Map<uint64_t, LimboState *> transitions;

	_FORCE_INLINE_ uint64_t _get_transition_key(Node *p_from_state, const String &p_event) {
		uint64_t key = hash_djb2_one_64(Variant::OBJECT);
		key = hash_djb2_one_64(Variant(p_from_state).hash(), key);
		key = hash_djb2_one_64(p_event.hash(), key);
		return key;
	}

protected:
	static void _bind_methods();

	void _notification(int p_what);

	virtual void _enter();
	virtual void _exit();
	virtual void _update(float p_delta);

	void _change_state(LimboState *p_state);

public:
	void set_update_mode(UpdateMode p_mode) { update_mode = p_mode; }
	UpdateMode get_update_mode() const { return update_mode; }

	LimboState *get_active_state() const { return active_state; };
	LimboState *get_leaf_state() const;
	void set_active(bool p_active);

	virtual void initialize(Object *p_agent, const Ref<Blackboard> &p_blackboard);
	virtual bool dispatch(const String &p_event, const Variant &p_cargo);

	void update(float p_delta) { _update(p_delta); }
	void add_transition(Node *p_from_state, Node *p_to_state, const String &p_event);
	LimboState *anystate() const { return nullptr; };

	LimboHSM();
};

#endif // LIMBO_HSM_H