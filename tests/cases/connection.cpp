//
// Created by Arthur Motelevicz on 30/07/24.
//
#include "TestsHelper.h"
#include <cedromd>

TEST_CASE("Connections")
{
  cedro::md::CMDBaseManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  std::promise<bool> sendPromise;
  std::future<bool> sendFuture = sendPromise.get_future();

  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  SECTION("Connection success")
  {

    manager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
    {
      streamPtr = stream;
      sendPromise.set_value(success);
    });

    TestHelper::waitForSuccess(sendFuture, streamPtr, 3);
  }

  SECTION("Connection failure - invalid credentials")
  {
    cedro::md::CMDBaseManager invalidManager("invalid_user", "invalid_password");

    std::promise<bool> failPromise;
    std::future<bool> failFuture = failPromise.get_future();

    invalidManager.connect([&](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
    {
      failPromise.set_value(success);
      streamPtr = stream;
    });

    TestHelper::waitForFail(failFuture, streamPtr, 8);
  }
}
