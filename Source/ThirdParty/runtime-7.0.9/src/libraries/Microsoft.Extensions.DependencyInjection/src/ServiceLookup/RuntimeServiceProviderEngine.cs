// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Diagnostics.CodeAnalysis;

namespace Microsoft.Extensions.DependencyInjection.ServiceLookup
{
    [RequiresDynamicCode(ServiceProvider.RequiresDynamicCodeMessage)]
    internal sealed class RuntimeServiceProviderEngine : ServiceProviderEngine
    {
        public static RuntimeServiceProviderEngine Instance { get; } = new RuntimeServiceProviderEngine();

        private RuntimeServiceProviderEngine() { }

        public override Func<ServiceProviderEngineScope, object?> RealizeService(ServiceCallSite callSite)
        {
            return scope =>
            {
                return CallSiteRuntimeResolver.Instance.Resolve(callSite, scope);
            };
        }
    }
}
