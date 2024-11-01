import unittest
import asyncpg
from unittest import IsolatedAsyncioTestCase
from sqlalchemy.ext.asyncio import create_async_engine, AsyncConnection
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.orm import sessionmaker
import aiosqlite


events = []

DATABASE_URL = "sqlite+aiosqlite:///./test.db"


class Test(IsolatedAsyncioTestCase):
    def setUp(self):
        events.append("setUp")

    async def asyncSetUp(self):
        async_engine = create_async_engine(DATABASE_URL, echo=True)
        self._async_connection = await async_engine.connect()
        events.append("asyncSetUp")

    async def test_response(self):
        events.append("test_response")
        async with self._async_connection.begin() as conn:
            # Example action with the connection (e.g., running a simple query)
            result = await conn.execute(text("SELECT 1"))
            self.assertEqual(result.scalar_one(), 1)
        self.addAsyncCleanup(self.on_cleanup)

    def tearDown(self):
        events.append("tearDown")

    async def asyncTearDown(self):
        await self._async_connection.close()
        events.append("asyncTearDown")

    async def on_cleanup(self):
        events.append("cleanup")


if __name__ == "__main__":
    unittest.main()

