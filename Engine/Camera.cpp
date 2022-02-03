#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"

Matrix Camera::S_MatView;
Matrix Camera::S_MatProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	// ī�޶��� ����Ŀ� ������� ���ָ� �װ� �ٷ� �亯ȯ �����.
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		// ���������̵� P���ϱ�
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	else
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);

	// �ӽ÷� ����� �͵�.
	S_MatView = _matView;
	S_MatProjection = _matProjection;
}

// �޽���������� ������Ʈ�� ����ִ¾ֵ鸸 ����
void Camera::Render()
{
	
	// ���Ŵ������� ���� Ȱ������ ������ �� �ܾ��
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();

	// TODO : Layer ����
	// �����ִ� ��� ������Ʈ�� ������
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		// �޽��������� ������ ��Ƽ��
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		gameObject->GetMeshRenderer()->Render();
	}
}