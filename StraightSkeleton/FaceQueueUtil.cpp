#include "FaceQueueUtil.h"

void FaceQueueUtil::MoveNodes(spfn firstFace, spfn secondFace)
{
	firstFace->AddQueue(secondFace);
}

void FaceQueueUtil::ConnectQueues(spfn firstFace, spfn secondFace)
{
	if (firstFace != nullptr && secondFace != nullptr)
	{
		if (firstFace->List == secondFace->List)
		{
			if (!firstFace->IsEnd() || !secondFace->IsEnd())
				throw std::runtime_error("try to connect the same list not on end nodes");
			if (firstFace->IsQueueUnconnected() || secondFace->IsQueueUnconnected())
				throw std::runtime_error("can't close node queue not conected with edges");

			firstFace->QueueClose();
			return;
		}
		if (!firstFace->IsQueueUnconnected() && !secondFace->IsQueueUnconnected())
			throw std::runtime_error("can't connect two diffrent queues if each of them is connected to edge");

		if (!firstFace->IsQueueUnconnected())
		{
			FaceQueue* qLeft = secondFace->List;
			MoveNodes(firstFace, secondFace);
			qLeft->Close();
		}
		else
		{
			FaceQueue* qRight = firstFace->List;
			MoveNodes(secondFace, firstFace);
			qRight->Close();
		}
	}
}
