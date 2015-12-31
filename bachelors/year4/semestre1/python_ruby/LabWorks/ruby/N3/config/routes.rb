Rails.application.routes.draw do

  # devise_for :users

  scope '(:locale)', locale: /en|uk/ do
    mount RailsAdmin::Engine => '/admin', as: 'rails_admin'

    match 'signup' => 'users#new', :via => [:get], :as => 'signup'
    match 'login' => 'sessions#login', :via => [:get], :as => 'login'
    match 'logout' => 'sessions#logout', :via => [:get], :as => 'logout'
    post 'sessions/login_attempt'
    match 'home' => 'sessions#home', :via => [:get], :as => 'home'
    match 'profile' => 'sessions#profile', :via => [:get], :as => 'profile'
    match 'settings' => 'sessions#setting', :via => [:get], :as => 'settings'
    match 'users' => 'users#show', :via => [:get], :as => 'users'
    match 'account' => 'accounts#show', :via => [:get], :as => 'account'

    resources :users do
      resources :credit_cards
      resources :accounts do
        resources :credit_cards
        post 'block'
        post 'unblock'
        post 'update_balance'
      end
    end
  end

  root 'users#new'
  # get '/:locale' => 'welcome#index'
  # root 'welcome#index'

  # The priority is based upon order of creation: first created -> highest priority.
  # See how all your routes lay out with "rake routes".

  # You can have the root of your site routed with "root"
  # root 'welcome#index'

  # Example of regular route:
  #   get 'products/:id' => 'catalog#view'

  # Example of named route that can be invoked with purchase_url(id: product.id)
  #   get 'products/:id/purchase' => 'catalog#purchase', as: :purchase

  # Example resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Example resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Example resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Example resource route with more complex sub-resources:
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', on: :collection
  #     end
  #   end

  # Example resource route with concerns:
  #   concern :toggleable do
  #     post 'toggle'
  #   end
  #   resources :posts, concerns: :toggleable
  #   resources :photos, concerns: :toggleable

  # Example resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end
end
