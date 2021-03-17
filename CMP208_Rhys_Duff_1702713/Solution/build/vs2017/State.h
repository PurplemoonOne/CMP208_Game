#pragma once


class Context;

class State
{
protected:

	Context* context;

public:

	virtual ~State() {}

	void SetContext(Context* context_) {
		this->context = context_;
	}

	virtual void OnEnter() = 0;
	virtual void Input(float delta_time) = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Render() = 0;
	virtual void OnExit() = 0;

};

