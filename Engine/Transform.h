#pragma once
#include "Component.h"

// Transform -> Position Rotation Scale
class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	virtual void FinalUpdate() override;
	void PushData();

public:
	// Parent ����
	const Vec3& GetLocalPosition() { return _localPosition; }
	const Vec3& GetLocalRotation() { return _localRotation; }
	const Vec3& GetLocalScale() { return _localScale; }

	// GetLocalToWorldMatrix�� �θ���� ���ο� ������� ��¥ ����� �������� ��ȯ���.
	const Matrix& GetLocalToWorldMatrix() { return _matWorld; }
	// ����������� ��� �ִ��� Ȯ���Ϸ��� GetWorldPosition()
	const Vec3& GetWorldPosition() { return _matWorld.Translation(); }

	// ���� ������.
	Vec3 GetRight() { return _matWorld.Right(); }
	Vec3 GetUp() { return _matWorld.Up(); }
	Vec3 GetLook() { return _matWorld.Backward(); }

	void SetLocalPosition(const Vec3& position) { _localPosition = position; }
	void SetLocalRotation(const Vec3& rotation) { _localRotation = rotation; }
	void SetLocalScale(const Vec3& scale) { _localScale = scale; }

public:
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	weak_ptr<Transform> GetParent() { return _parent; }

private:
	// ���� �����̾ƴ϶� Parent ���� ������ǥ�̴�. 10_0 Cube
	// �ڱⰡ �ֻ��������̸� �������(0,0) ����.
	Vec3 _localPosition = {};
	Vec3 _localRotation = {};
	Vec3 _localScale = { 1.f, 1.f, 1.f };

	// _matLocal�� �θ�Ա���
	Matrix _matLocal = {};
	Matrix _matWorld = {};

	// �θ��� ������ ��� ���� Ʈ������
	weak_ptr<Transform> _parent;
};

