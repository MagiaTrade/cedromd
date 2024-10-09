//
// Created by Arthur Motelevicz on 30/07/24.
//
#include "TestsHelper.h"
#include <cedromd>

TEST_CASE("Connection success")
{
  cedro::md::CMDBaseManager manager(CEDRO_USERNAME, CEDRO_PASSWORD, CEDRO_SOFTKEY);

  auto sendPromise = std::make_shared<std::promise<bool>>();
  std::future<bool> sendFuture = sendPromise->get_future();
  std::shared_ptr<bb::network::rs::Stream> streamPtr;

  auto _promiseSet = std::make_shared<std::atomic<bool>>();
  _promiseSet->store(false);

  manager.connect([&,sendPromise, _promiseSet](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
  {
    auto previousValue  = _promiseSet->exchange(true);
    if(previousValue)
      return;

    streamPtr = stream;
    sendPromise->set_value(success);
  });

  TestHelper::waitForSuccess(sendFuture, streamPtr, 3);
}

TEST_CASE("Connection failure")
{
  cedro::md::CMDBaseManager invalidManager("invalid_user", "invalid_password");
  std::shared_ptr<bb::network::rs::Stream> streamPtr;
  std::shared_ptr<std::promise<bool>> failPromise = std::make_shared<std::promise<bool>>();
  std::future<bool> failFuture = failPromise->get_future();
  auto _promiseSet = std::make_shared<std::atomic<bool>>();
  _promiseSet->store(false);

  invalidManager.connect([&, failPromise, _promiseSet](bool success, const std::shared_ptr<bb::network::rs::Stream>& stream)
  {
    auto previousValue  = _promiseSet->exchange(true);
    if(previousValue)
      return;

    failPromise->set_value(success);
    streamPtr = stream;
  });

  TestHelper::waitForFail(failFuture, streamPtr, 8);
}

