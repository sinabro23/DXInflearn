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
	// Parent 기준
	const Vec3& GetLocalPosition() { return _localPosition; }
	const Vec3& GetLocalRotation() { return _localRotation; }
	const Vec3& GetLocalScale() { return _localScale; }

	// GetLocalToWorldMatrix는 부모님의 여부와 상관없이 진짜 월드로 가기위한 변환행렬.
	const Matrix& GetLocalToWorldMatrix() { return _matWorld; }
	// 월드기준으로 어디에 있는지 확인하려면 GetWorldPosition()
	const Vec3& GetWorldPosition() { return _matWorld.Translation(); }

	// 월드 기준임.
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
	// 월드 기준이아니라 Parent 기준 로컬좌표이다. 10_0 Cube
	// 자기가 최상위계층이면 월드기준(0,0) 맞음.
	Vec3 _localPosition = {};
	Vec3 _localRotation = {};
	Vec3 _localScale = { 1.f, 1.f, 1.f };

	// _matLocal은 부모님기준
	Matrix _matLocal = {};
	Matrix _matWorld = {};

	// 부모의 정보를 들고 있을 트랜스폼
	weak_ptr<Transform> _parent;
};

