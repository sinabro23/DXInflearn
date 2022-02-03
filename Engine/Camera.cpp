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
	// 카메라의 뷰행렬에 역행렬을 해주면 그게 바로 뷰변환 행렬임.
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_type == PROJECTION_TYPE::PERSPECTIVE)
		// 원근적용이된 P구하기
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	else
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);

	// 임시로 사용할 것들.
	S_MatView = _matView;
	S_MatProjection = _matProjection;
}

// 메쉬렌더러라는 컴포넌트를 들고있는애들만 렌더
void Camera::Render()
{
	
	// 씬매니저에서 현재 활동중인 씬들을 다 긁어옴
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();

	// TODO : Layer 구분
	// 씬에있는 모든 오브젝트를 가져옴
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		// 메쉬렌더러가 없으면 컨티뉴
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		gameObject->GetMeshRenderer()->Render();
	}
}